
#include "tinyxml2.h"

#include "s4n.h"

#include "envoy/buffer/buffer.h"
#include "common/buffer/buffer_impl.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Filter {

const std::string S4N::S4N_CONTENT_TYPE = "application/s4n";

Http::FilterHeadersStatus S4N::decodeHeaders(Http::HeaderMap& headers, bool){
  const Http::HeaderEntry * content_type = headers.ContentType();
  s4n_request_ = content_type && content_type->value() == S4N_CONTENT_TYPE.c_str();
  return Http::FilterHeadersStatus::Continue;
}

Http::FilterDataStatus S4N::decodeData(Buffer::Instance& /*data*/, bool end_stream){
  if (!s4n_request_) 
    return Http::FilterDataStatus::Continue;

  const Buffer::Instance * decoding_buffer = decoder_callbacks_->decodingBuffer();

  if (!end_stream || !decoding_buffer) 
    return Http::FilterDataStatus::StopIterationAndBuffer;

  //TODO: workarround having to copy and copy and copy buffers
  Buffer::OwnedImpl oldDat(*decoding_buffer);
  auto all_raw = static_cast<const char*>(oldDat.linearize(oldDat.length()));

  using namespace tinyxml2;
  XMLDocument doc;
  doc.Parse(static_cast<const char*>(all_raw), oldDat.length());
  auto pRoot = doc.FirstChildElement("cc");
  if( pRoot){
    //auto cleartext = pRoot->GetText();
    const char * encodedtext = "encoded text";
    pRoot->SetText(encodedtext);
  }
  XMLPrinter printer;
  //printer.SetIndent( " " );
  doc.Accept(&printer);

  Buffer::OwnedImpl newDat;
  newDat.add(printer.CStr());
  decoder_callbacks_->encodeData(newDat, true );

  return Http::FilterDataStatus::Continue;
}

Http::FilterTrailersStatus S4N::decodeTrailers(Http::HeaderMap&){
  return Http::FilterTrailersStatus::Continue;
}

void S4N::setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // Filter
} // Envoy
