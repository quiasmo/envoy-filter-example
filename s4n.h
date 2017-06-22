#pragma once

#include "envoy/http/filter.h"

#include "common/common/logger.h"

namespace Envoy {
namespace Filter {

/**
 * Implementation of a basic echo filter.
 */
class S4N : public Http::StreamDecoderFilter, Logger::Loggable<Logger::Id::filter> {
public:

  static const std::string S4N_CONTENT_TYPE;

  virtual void onDestroy() override {};
  virtual Http::FilterHeadersStatus decodeHeaders(Http::HeaderMap& headers, bool end_stream) override;
  virtual Http::FilterDataStatus decodeData(Buffer::Instance& data, bool end_stream) override;
  virtual Http::FilterTrailersStatus decodeTrailers(Http::HeaderMap& trailers) override;
  void setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override;

private:
  Http::StreamDecoderFilterCallbacks* decoder_callbacks_{};
  bool s4n_request_;
};

} // Filter
} // Envoy
