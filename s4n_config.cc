#include <string>

#include "s4n.h"
#include "server/configuration_impl.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Config registration for the s4n filter. @see  NamedHttpFilterConfigFactory.
 */
class S4NConfigFactory : public NamedHttpFilterConfigFactory {
public:
  // NamedHttpFilterConfigFactory
  HttpFilterFactoryCb createFilterFactory(const Json::Object& /*config*/,
                                          const std::string& /*stat_prefix*/,
                                          FactoryContext& /*context*/) override {
    
    return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{new Filter::S4N()});
    };
  }

  std::string name() override { return "S4N"; }
  HttpFilterType type() override { return HttpFilterType::Decoder; }
};

/**
 * Static registration for the s4n filter. @see NamedNetworkFilterConfigFactory.
 */
static Registry::RegisterFactory<S4NConfigFactory, NamedHttpFilterConfigFactory> registered_;

} // Configuration
} // Server
} // Envoy
