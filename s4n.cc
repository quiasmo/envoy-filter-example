#include <tinyxml2.h>

#include "s4n.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Filter {

HTTP::FilterHeadersStatus S4N::decodeHeaders(HeaderMap& headers, bool end_stream){
  const Http::HeaderEntry * content_type = headers.ContentType();
  s4n_request_ = content_type && content_type->value() == S4N_CONTENT_TYPE.c_str();
  return HTTP::FilterHeadersStatus::Continue;
}

HTTP::FilterDataStatus S4N::decodeData(Buffer::Instance& data, bool end_stream){
  if (!s4n_request_) 
    return Http::FilterDataStatus::Continue;

  auto decoding_buffer = decoder_callbacks_->decodingBuffer();

  if (!end_stream || !decoding_buffer) 
    return Http::FilterDataStatus::StopIterationAndBuffer;


  using namespace tinyxml2;

  auto all_raw = static_cast<const char*>(decoding_buffer->linearize(decoding_buffer->length()));

  TiXmlDocument doc;
  doc.Parse((const char*)all_raw, decoding_buffer->length());
  pRoot = doc.FirstChildElement("cc");
  if( pRoot){
    auto cleartext = pRoot->GetText();
    auto encodedtext = "encoded text";
    pRoot->SetText(encoded);
  }
  TiXmlPrinter printer;
  printer.SetIndent( " " );
  doc.Accept(&printer);

  Buffer::OwnedImpl newDat;
  newDat.add(printer.CStr())
  decoder_callbacks_->encodeData(newDat, true );

  return Http::FilterDataStatus::Continue;
}

HTTP::FilterTrailersStatus S4N::decodeTrailers(HeaderMap& trailers){
  return HTTP::FilterTrailersStatus::Continue;
}

void S4N::setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override {
  decoder_callbacks_ = &callbacks;
}

} // Filter
} // Envoy
