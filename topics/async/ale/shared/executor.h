#pragma once

#include <functional>
#include "non-gsl.h"
#include <vector>

struct Executor;
namespace detail {
Executor*& get_current_executor_holder();
}

struct Executor {
  using WorkQueue = std::vector<std::function<void()>>;

  void add_work(std::function<void()> fn) {
    work_.emplace_back(std::move(fn));
  }

  void execute() {
    const auto cleanup = non_gsl::finally([&] {
       detail::get_current_executor_holder() = nullptr;
    });
    detail::get_current_executor_holder() = this;

    while (not work_.empty()) {
      auto pending_work = WorkQueue{};
      swap(pending_work, work_);
      for (auto&& fn : pending_work) {
        fn();
      }
    }
  }

  WorkQueue work_;
};

inline Executor& get_current_executor() {
  return *detail::get_current_executor_holder();
}
