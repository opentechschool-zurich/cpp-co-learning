#include <iostream>
#include <cassert>
#include "../shared/non-gsl.h"
#include "http_client.h"
#include "../shared/http_client_implementations.h"

namespace synchronous {

std::vector<std::string>
	request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request) {
		(void)http_client;
		(void)uris_to_request;
		return {"42"};
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
