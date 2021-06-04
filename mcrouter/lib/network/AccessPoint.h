/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <string>

#include <folly/Range.h>

#include "mcrouter/lib/mc/protocol.h"
#include "mcrouter/lib/network/SecurityOptions.h"

namespace folly {
class IPAddress;
} // namespace folly

namespace facebook {
namespace memcache {

struct McProtocolT {
  operator mc_protocol_t() const {
    return static_cast<mc_protocol_t>(data_);
  }

  explicit McProtocolT(mc_protocol_t proto = mc_unknown_protocol)
      : data_(proto) {}
  McProtocolT& operator=(mc_protocol_t proto) {
    data_ = proto;
    return *this;
  }

  uint8_t data_;
};

static_assert(
    sizeof(McProtocolT) == sizeof(uint8_t),
    "McProtocolT must have uint8_t size");
static_assert(
    std::alignment_of<McProtocolT>::value == std::alignment_of<uint8_t>::value,
    "McProtocolT must have uint8_t alignemnt");

struct AccessPoint {
  explicit AccessPoint(
      folly::StringPiece host = "",
      uint16_t port = 0,
      mc_protocol_t protocol = mc_unknown_protocol,
      SecurityMech mech = SecurityMech::NONE,
      bool compressed = false,
      bool unixDomainSocket = false,
      uint32_t failureDomain = 0);

  AccessPoint(
      const folly::IPAddress& addr,
      uint16_t port,
      uint32_t failureDomain = 0,
      mc_protocol_t protocol = mc_unknown_protocol);

  /**
   * Constructor used by SRRoute where AccessPoints need to be
   * constructed on the fly for logging purposes only and only require
   * the IP in string format
   */
  struct HostOnlyTag {};
  AccessPoint(
      HostOnlyTag,
      const std::string_view host,
      mc_protocol_t protocol = mc_unknown_protocol)
      : host_(host), port_(0), protocol_(protocol) {}

  /**
   * @param apString accepts host:port, host:port:protocol and
   *                 host:port:protocol:(ssl|plain):(compressed|notcompressed)
   * @param defaultProtocol this is the protocol used if no protocol specified
   * @param defaultMech this is the default security protocol used if
                        not specified
   * @param portOverride This overrides the port. If 0, port from
   *                     hostPortProtocol used
   * @param defaultCompressed The is the compression config to use if it's not
   *                          specified in the string.
   *
   * @return shared_ptr to an AccessPoint object
   */
  static std::shared_ptr<AccessPoint> create(
      folly::StringPiece apString,
      mc_protocol_t defaultProtocol,
      SecurityMech defaultMech = SecurityMech::NONE,
      uint16_t portOverride = 0,
      bool defaultCompressed = false,
      uint32_t failureDomain = 0);

  const std::string& getHost() const {
    return host_;
  }

  uint64_t getHash() const {
    return hash_;
  }

  uint16_t getPort() const {
    return port_;
  }

  mc_protocol_t getProtocol() const {
    return protocol_;
  }

  SecurityMech getSecurityMech() const {
    return securityMech_;
  }

  uint32_t getFailureDomain() const {
    return failureDomain_;
  }

  bool useSsl() const {
    return securityMech_ != SecurityMech::NONE;
  }

  bool compressed() const {
    return compressed_;
  }

  bool isUnixDomainSocket() const {
    return unixDomainSocket_;
  }

  /**
   * @return [host]:port if address is IPv6, host:port otherwise
   */
  std::string toHostPortString() const;

  /**
   * @return HostPort:protocol:(ssl|plain) string
   */
  std::string toString() const;

  void disableCompression();

  void setSecurityMech(SecurityMech mech) {
    securityMech_ = mech;
  }

  void setPort(uint16_t port) {
    port_ = port;
  }

 private:
  std::string host_;
  uint64_t hash_{0};
  uint16_t port_;
  McProtocolT protocol_;
  SecurityMech securityMech_{SecurityMech::NONE};
  bool compressed_{false};
  bool isV6_{false};
  bool unixDomainSocket_{false};
  uint32_t failureDomain_{0};
};

} // namespace memcache
} // namespace facebook
