#include <string>

#include "echo2.h"
#include "server/configuration_impl.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Config registration for the echo2 filter. @see  NamedNetworkFilterConfigFactory.
 */
class Echo2ConfigFactory : public NamedNetworkFilterConfigFactory {
public:
  // NamedNetworkFilterConfigFactory
  NetworkFilterFactoryCb createFilterFactory(const Json::Object&, FactoryContext&) override {
    return [](Network::FilterManager& filter_manager)
        -> void { filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::Echo2()}); };
  }

  std::string name() override { return "echo2"; }
  NetworkFilterType type() override { return NetworkFilterType::Read; }
};

/**
 * Static registration for the echo2 filter. @see NamedNetworkFilterConfigFactory.
 */
static Registry::RegisterFactory<Echo2ConfigFactory, NamedNetworkFilterConfigFactory> registered_;

} // Configuration
} // Server
} // Envoy
