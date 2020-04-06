/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "WeightedRendezvousHashFunc.h"

#include <cassert>
#include <cmath>

#include <glog/logging.h>

#include "mcrouter/lib/RendezvousHashHelper.h"
#include "mcrouter/lib/fbi/cpp/util.h"
#include "mcrouter/lib/fbi/hash.h"

namespace facebook {
namespace memcache {

WeightedRendezvousHashFunc::WeightedRendezvousHashFunc(
    const std::vector<folly::StringPiece>& endpoints,
    const folly::dynamic& json) {
  checkLogic(json.isObject(), "WeightedRendezvousHashFunc: not an object");
  checkLogic(json.count("weights"), "WeightedRendezvousHashFunc: no weights");
  const auto& jWeights = json["weights"];
  checkLogic(
      jWeights.isArray(),
      "WeightedRendezvousHashFunc: weights is not an array");

  checkLogic(
      jWeights.size() == endpoints.size(),
      "WeightedRendezvousHash: number of weights doesn't match number of end points.");

  // Compute hash and decode weight for each endpoint.
  endpointHashes_.reserve(endpoints.size());
  endpointWeights_.reserve(endpoints.size());
  assert(endpointHashes_.empty());
  assert(endpointWeights_.empty());

  for (size_t i = 0; i < endpoints.size(); ++i) {
    const uint64_t hash = murmur_hash_64A(
        endpoints[i].data(), endpoints[i].size(), kRendezvousHashSeed);
    endpointHashes_.push_back(hash);
    endpointWeights_.push_back(jWeights[i].asDouble());
  }
}

size_t WeightedRendezvousHashFunc::operator()(folly::StringPiece key) const {
  double maxScore = 0;
  size_t maxScorePos = 0;

  const uint64_t keyHash =
      murmur_hash_64A(key.data(), key.size(), kRendezvousExtraHashSeed);

  for (size_t i = 0; i < endpointHashes_.size(); ++i) {
    uint64_t scoreInt = hash128to64(endpointHashes_[i], keyHash);
    // Borrow from https://en.wikipedia.org/wiki/Rendezvous_hashing.
    double score = endpointWeights_[i] *
        (1.0 / (-std::log(convertInt64ToDouble01(scoreInt))));
    if (score > maxScore) {
      maxScore = score;
      maxScorePos = i;
    }
  }

  return maxScorePos;
}
} // namespace memcache
} // namespace facebook
