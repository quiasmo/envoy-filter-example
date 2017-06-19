#include <string>

#include "s4n.h"
#include "server/configuration_impl.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Config registration for the s4n filter. @see  NamedNetworkFilterConfigFactory.
 */
class S4NConfigFactory : public NamedNetworkFilterConfigFactory {
public:
  // NamedNetworkFilterConfigFactory
  NetworkFilterFactoryCb createFilterFactory(const Json::Object&, FactoryContext&) override {
    return [](Network::FilterManager& filter_manager)
        -> void { filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::S4N()}); };
  }

  std::string name() override { return "S4N"; }
  NetworkFilterType type() override { return NetworkFilterType::Read; }
};

/**
 * Static registration for the s4n filter. @see NamedNetworkFilterConfigFactory.
 */
static Registry::RegisterFactory<S4NConfigFactory, NamedNetworkFilterConfigFactory> registered_;

} // Configuration
} // Server
} // Envoy
