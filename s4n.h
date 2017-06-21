#pragma once

#include "envoy/network/filter.h"

#include "common/common/logger.h"

namespace Envoy {
namespace Filter {

/**
 * Implementation of a basic echo filter.
 */
class S4N : public HTTP::StreamDecoderFilter, Logger::Loggable<Logger::Id::filter> {
public:

  static const string S4N_CONTENT_TYPE{"application/s4n"};

  virtual HTTP::FilterHeadersStatus decodeHeaders(HeaderMap& headers, bool end_stream) override;
  virtual HTTP::FilterDataStatus decodeData(Buffer::Instance& data, bool end_stream) override;
  virtual HTTP::FilterTrailersStatus decodeTrailers(HeaderMap& trailers) override;
  void setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override;

private:
  Http::StreamDecoderFilterCallbacks* decoder_callbacks_{};
  bool s4n_request_;
};

} // Filter
} // Envoy
