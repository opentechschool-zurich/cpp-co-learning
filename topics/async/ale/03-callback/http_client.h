#pragma once

#include <string>
#include <variant>
#include <vector>
#include <functional>

#include "../shared/http_client.h"

namespace callback {

class HttpClient {
	public:
		virtual ~HttpClient() = default;
		virtual void request_get(const std::string& uri,
		const std::function<void(HttpResponse)>& cb) = 0;
};

void request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request,
	const std::function<void(std::vector<std::string>)>& cb);
}
