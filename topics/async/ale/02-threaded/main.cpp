#include <iostream>
#include <cassert>
#include <mutex>
#include <algorithm>
#include "http_client.h"
#include "../shared/http_client_implementations.h"

#include <thread>

namespace threaded {

std::mutex mtx;

void call(std::string uri, HttpClient& http_client, std::vector<std::string>& result)
{
    auto response = http_client.request_get(uri);
    while (std::holds_alternative<Redirect>(response)) {
        response = http_client.request_get(std::get<Redirect>(response).target);
    }
    if (std::holds_alternative<Content>(response)) {
        mtx.lock();
        result.push_back(std::get<Content>(response).content);
        mtx.unlock();
    }
}

std::vector<std::string> request_uris(HttpClient& http_client,
	const std::vector<std::string>& uris_to_request)
{
    std::vector<std::thread> threads{};
    std::vector<std::string> result{};

    for (auto uri: uris_to_request) {
        http_client.request_get(uri);
        threads.push_back(std::move(std::thread(call, uri, std::ref(http_client), std::ref(result))));
    }

    for (auto& thread: threads) {
        thread.join();
    }

    return result;
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
