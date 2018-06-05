#include "../01-sync/http_client.h"
#include "../02-threaded/http_client.h"
#include "../03-callback/http_client.h"
#include "../04-task/http_client.h"
// #include "../05-boost_coroutine/http_client.h"
// #include "../06-coroutine_ts/http_client.h"

#include "executor.h"

#include <sstream>
#include "non-boost.h"

#include "non-gsl.h"

static std::ostream& get_logger() {
#if 1
  static std::stringstream null_strm;
  return null_strm;
#else
  return std::cerr;
#endif
}

static inline auto& log_msg = get_logger();

static HttpResponse request_get_impl(std::string_view uri) {
  if (uri == "/file1") {
    return Redirect{"/newplaceoffile1"};
  }
  if (uri == "/newplaceoffile1") {
    return Redirect{"/file2"};
  }
  if (uri == "/file2") {
    return Content{"content1"};
  }
  if (uri == "/file3") {
    return Content{"content2"};
  }
  if (non_boost::algorithm::starts_with(uri, "/extremeredirect")) {
    std::vector<std::string> parts;
    non_boost::algorithm::split(parts, uri, [](char c) { return c == '/'; });
    if (parts.size() == 2) {
      return Redirect{std::string{uri} + "/1"};
    }
    if (parts.size() == 3) {
      auto num = std::stol(parts[2]);
      if (num < 4) {
        return Redirect{"/extremeredirect/" + std::to_string(num + 1)};
      }
    }
    return Content{"finally here"};
  }
  return Content{""};
}

namespace synchronous {
class ConcreteHttpClient : public HttpClient {
public:
  HttpResponse request_get(std::string_view uri) override {
    log_msg << "request " << uri << "..." << std::endl;
    auto out
        = non_gsl::finally([&] { log_msg << "...request " << uri << std::endl; });
    return request_get_impl(uri);
  }
};
}

namespace threaded {
class ConcreteHttpClient : public HttpClient {
public:
  HttpResponse request_get(std::string_view uri) override {
    log_msg << "request " << uri << "..." << std::endl;
    auto out
        = non_gsl::finally([&] { log_msg << "...request " << uri << std::endl; });
    return request_get_impl(uri);
  }
};
}

namespace callback {

class ConcreteHttpClient : public HttpClient {
public:
  void request_get(const std::string& uri, const std::function<void(HttpResponse)>& cb) override {
    log_msg << "request " << uri << "..." << std::endl;
    auto handle = [uri]() -> HttpResponse { return request_get_impl(uri); };
    get_current_executor().add_work([=] {
      log_msg << "...request " << uri << std::endl;
      get_current_executor().add_work([=] { cb(handle()); });
    });
  }
};
}

/*
namespace task_based {

class ConcreteHttpClient : public HttpClient {
public:
  task<HttpResponse> request_get(const std::string& uri) override {
    log_msg << "request " << uri << "..." << std::endl;
    const auto handle
      = [uri]() -> HttpResponse { return request_get_impl(uri); };

    auto fut = make_task<HttpResponse>();
    get_current_executor().add_work([=] {
      log_msg << "...request " << uri << std::endl;

      fut->set_result(handle());
    });
    return fut;
  }
};
}

namespace boost_coroutine {

class ConcreteHttpClient : public HttpClient {
public:
  task<HttpResponse> request_get(const std::string& uri) override {
    log_msg << "request " << uri << "..." << std::endl;
    const auto handle = [=]() -> HttpResponse { return request_get_impl(uri); };

    auto fut = make_task<HttpResponse>();
    get_current_executor().add_work([=] {
      log_msg << "...request " << uri << std::endl;
      fut->set_result(handle());
    });
    return fut;
  }
};
}

namespace coroutines_ts {

class ConcreteHttpClient : public HttpClient {
public:
  task<HttpResponse> request_get(const std::string& uri) override {
    log_msg << "request " << uri << "..." << std::endl;
    const auto handle = [=]() -> HttpResponse { return request_get_impl(uri); };

    auto fut = make_task<HttpResponse>();
    get_current_executor().add_work([=] {
      log_msg << "...request " << uri << std::endl;
      fut->set_result(handle());
    });
    return fut;
  }
};
}
*/
