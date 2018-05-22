#include <iostream>
#include <cassert>
#include "http_client.h"
#include "../shared/http_client_implementations.h"

namespace synchronous {

std::vector<std::string> request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request)
{
    std::vector<std::string> result{};
    for (auto uri: uris_to_request) {
        auto response = http_client.request_get(uri);
        while (std::holds_alternative<Redirect>(response)) {
            response = http_client.request_get(std::get<Redirect>(response).target);
        }
        if (std::holds_alternative<Content>(response)) {
            result.push_back(std::get<Content>(response).content);
        }
    }
    return result;
}

}

int main()
{

	using namespace synchronous;

	auto http_client = ConcreteHttpClient{};

	auto result = request_uris(
		http_client, {"/file1", "/file2", "/file3", "/extremeredirect"}
	);

	
    assert(result.at(0) == "content1");
    assert(result.at(1) == "content1");
    assert(result.at(2) == "content2");
    assert(result.at(3) == "finally here");
}
