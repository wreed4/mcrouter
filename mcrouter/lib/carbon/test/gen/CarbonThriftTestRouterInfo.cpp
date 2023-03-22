/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */
#include "CarbonThriftTestRouterInfo.h"

#include <unordered_map>

#include <folly/Range.h>
#include <folly/dynamic.h>

#include <mcrouter/routes/ExtraRouteHandleProviderIf.h>
#include <mcrouter/routes/McRouteHandleProvider.h>

#include <mcrouter/lib/routes/NullRoute.h>
#include <mcrouter/routes/AllAsyncRouteFactory.h>
#include <mcrouter/routes/AllFastestRouteFactory.h>
#include <mcrouter/routes/AllInitialRouteFactory.h>
#include <mcrouter/routes/AllMajorityRouteFactory.h>
#include <mcrouter/routes/AllSyncRouteFactory.h>
#include <mcrouter/routes/BlackholeRoute.h>
#include <mcrouter/routes/DevNullRoute.h>
#include <mcrouter/routes/ErrorRoute.h>
#include <mcrouter/routes/FailoverRoute.h>
#include <mcrouter/routes/HashRouteFactory.h>
#include <mcrouter/routes/HostIdRouteFactory.h>
#include <mcrouter/routes/LatencyInjectionRoute.h>
#include <mcrouter/routes/LatestRoute.h>
#include <mcrouter/routes/LoadBalancerRoute.h>
#include <mcrouter/routes/LoggingRoute.h>
#include <mcrouter/routes/MigrateRouteFactory.h>
#include <mcrouter/routes/MissFailoverRoute.h>
#include <mcrouter/routes/ModifyKeyRoute.h>
#include <mcrouter/routes/OperationSelectorRoute.h>
#include <mcrouter/routes/OutstandingLimitRoute.h>
#include <mcrouter/routes/RandomRouteFactory.h>

#include <mcrouter/routes/McExtraRouteHandleProvider.h>

using namespace facebook::memcache;
using namespace facebook::memcache::mcrouter;

namespace carbon {
namespace test {

constexpr const char* CarbonThriftTestRouterInfo::name;

/* static */ CarbonThriftTestRouterInfo::RouteHandleFactoryMap
CarbonThriftTestRouterInfo::buildRouteMap() {
  RouteHandleFactoryMap map{
      {"AllAsyncRoute", &makeAllAsyncRoute<CarbonThriftTestRouterInfo>},
      {"AllFastestRoute", &makeAllFastestRoute<CarbonThriftTestRouterInfo>},
      {"AllInitialRoute", &makeAllInitialRoute<CarbonThriftTestRouterInfo>},
      {"AllMajorityRoute", &makeAllMajorityRoute<CarbonThriftTestRouterInfo>},
      {"AllSyncRoute", &makeAllSyncRoute<CarbonThriftTestRouterInfo>},
      {"BlackholeRoute", &makeBlackholeRoute<CarbonThriftTestRouterInfo>},
      {"DevNullRoute", &makeDevNullRoute<CarbonThriftTestRouterInfo>},
      {"ErrorRoute", &makeErrorRoute<CarbonThriftTestRouterInfo>},
      {"HashRoute",
       [](RouteHandleFactory<RouteHandleIf>& factory,
          const folly::dynamic& json) {
         return makeHashRoute<CarbonThriftTestRouterInfo>(factory, json);
       }},
      {"HostIdRoute", &makeHostIdRoute<CarbonThriftTestRouterInfo>},
      {"LatencyInjectionRoute",
       &makeLatencyInjectionRoute<CarbonThriftTestRouterInfo>},
      {"LatestRoute", &makeLatestRoute<CarbonThriftTestRouterInfo>},
      {"LoadBalancerRoute", &makeLoadBalancerRoute<CarbonThriftTestRouterInfo>},
      {"LoggingRoute", &makeLoggingRoute<CarbonThriftTestRouterInfo>},
      {"MigrateRoute", &makeMigrateRoute<CarbonThriftTestRouterInfo>},
      {"MissFailoverRoute", &makeMissFailoverRoute<CarbonThriftTestRouterInfo>},
      {"ModifyKeyRoute", &makeModifyKeyRoute<CarbonThriftTestRouterInfo>},
      {"NullRoute", &makeNullRoute<CarbonThriftTestRouteHandleIf>},
      {"OperationSelectorRoute",
       &makeOperationSelectorRoute<CarbonThriftTestRouterInfo>},
      {"RandomRoute", &makeRandomRoute<CarbonThriftTestRouterInfo>},
  };
  return map;
}

/* static */ CarbonThriftTestRouterInfo::RouteHandleFactoryMapWithProxy
CarbonThriftTestRouterInfo::buildRouteMapWithProxy() {
  return RouteHandleFactoryMapWithProxy();
}

/* static */ CarbonThriftTestRouterInfo::RouteHandleFactoryMapForWrapper
CarbonThriftTestRouterInfo::buildRouteMapForWrapper() {
  return RouteHandleFactoryMapForWrapper();
}

/* static */
std::unique_ptr<ExtraRouteHandleProviderIf<CarbonThriftTestRouterInfo>>
CarbonThriftTestRouterInfo::buildExtraProvider() {
  return std::make_unique<McExtraRouteHandleProvider<CarbonThriftTestRouterInfo>>();
}
} // namespace test
} // namespace carbon
