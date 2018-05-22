#pragma once

#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "../shared/http_client.h"

namespace synchronous {

class HttpClient {
public:
  virtual ~HttpClient()                                  = default;
  virtual HttpResponse request_get(std::string_view uri) = 0;
};

std::vector<std::string>
request_uris(HttpClient& http_client,
    const std::vector<std::string>& uris_to_request);
}
