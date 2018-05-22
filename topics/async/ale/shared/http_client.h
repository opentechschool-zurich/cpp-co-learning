#pragma once

#include <string>
#include <variant>

struct Redirect {
  std::string target;
};
struct Content {
  std::string content;
};

using HttpResponse = std::variant<Redirect, Content>;
