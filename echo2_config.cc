#include <string>

#include "echo2.h"
#include "server/configuration_impl.h"
#include "server/filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Config registration for the echo2 filter. @see NetworkFilterConfigFactory.
 */
class Echo2ConfigFactory : public NetworkFilterConfigFactory {
public:
  // NetworkFilterConfigFactory
  NetworkFilterFactoryCb createFilterFactory(const Json::Object&, FactoryContext&) override {
    return [](Network::FilterManager& filter_manager)
        -> void { filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::Echo2()}); };
  }

  std::string name() override { return "echo2"; }
  NetworkFilterType type() override { return NetworkFilterType::Read; }
};

/**
 * Static registration for the echo2 filter. @see RegisterNetworkFilterConfigFactory.
 */
static RegisterFactory<Echo2ConfigFactory, NetworkFilterConfigFactory> registered_;

} // Configuration
} // Server
} // Envoy
