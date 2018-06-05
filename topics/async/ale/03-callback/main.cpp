#include <cassert>
#include "http_client.h"
#include "../shared/http_client_implementations.h"

namespace callback {

void call(std::string uri, HttpClient& http_client, std::vector<std::string>& result)
{
}

void request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request,
	const std::function<void(std::vector<std::string>)>& cb)
{
    (void)http_client;
    (void)uris_to_request;
	cb({"42"});
}

}

int main()
{

	using namespace callback;

	auto executor = Executor{};
	auto http_client = ConcreteHttpClient{};

	auto result = std::vector<std::string>{};

	executor.add_work([&] {
		request_uris(http_client,
			{"/file1", "/file2", "/file3", "/extremeredirect"},
			[&](auto callback_result) { result = callback_result; });
	});
	executor.execute();

    std::vector<std::string> expect{"content1", "content1", "content2", "finally here"};
    assert(std::is_permutation(result.begin(), result.end(), expect.begin()));
}
