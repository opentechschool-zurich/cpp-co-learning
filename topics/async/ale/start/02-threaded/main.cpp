#include <cassert>
#include "http_client.h"
#include "../shared/http_client_implementations.h"

namespace threaded {

std::vector<std::string> request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request)
{
    (void)http_client;
    (void)uris_to_request;
    return {"42"};
}

}

int main()
{

	using namespace threaded;

	auto http_client = ConcreteHttpClient{};

	auto result = request_uris(
		http_client, {"/file1", "/file2", "/file3", "/extremeredirect"}
	);

    std::vector<std::string> expect{"content1", "content1", "content2", "finally here"};
    assert(std::is_permutation(result.begin(), result.end(), expect.begin()));
}
