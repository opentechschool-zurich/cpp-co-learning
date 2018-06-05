#pragma once

// #include <boost/hana.hpp>
#include <iostream>
#include <cassert>
#include <optional>
#include <type_traits>
#include <memory>
#include <vector>

#include "executor.h"

struct Executor;
Executor& get_current_executor();

namespace impl {
template <typename T>
class task_impl;

template <typename T>
using task = std::shared_ptr<task_impl<T>>;
}

template <typename T>
using task = impl::task<T>;

template <typename T>
task<T> make_task();

template <typename T>
task<T>    create_finished_task(T result);
task<void> create_finished_task();

namespace impl {

struct task_impl_tag {};

template <typename T>
struct is_shared_ptr;

template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : public std::true_type {};

template <typename T>
struct is_shared_ptr : public std::false_type {};

template <typename T>
constexpr bool is_task_impl() {
  if constexpr (is_shared_ptr<T>::value) {
    if constexpr (std::is_base_of_v<task_impl_tag, typename T::element_type>) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

class then_impl_accessor {
public:
  template <typename T>
  static auto& get_data(T* pThis) {
    return pThis->data;
  }
};

template <typename T>
struct type {
  using value_type = T;
};

template <typename TCont>
auto get_real_cont_type() {
  if constexpr (is_task_impl<TCont>()) {
    if constexpr (std::is_same_v<typename TCont::element_type::value_type,
                                 void>) {
      return type<void>{};
    } else {
      return type<typename TCont::element_type::value_type>{};
    }
  } else {
    return type<TCont>{};
  }
}

template <typename Ttask, typename TCont, typename TListener>
auto then_impl(task_impl<Ttask>* pThis, TListener&& listener) {
  using real_cont_type =
    typename decltype(get_real_cont_type<TCont>())::value_type;
  auto data          = then_impl_accessor::get_data(pThis);
  auto call_listener = [data](auto&& local_listener) mutable {
    if constexpr (std::is_same_v<Ttask, void>) {
      (void)data;
      return local_listener();
    } else {
      return local_listener(*data->result_);
    }
  };
  bool result_is_available = false;
  if constexpr (std::is_same_v<Ttask, void>) {
    result_is_available = data->result_;
  } else {
    result_is_available = data->result_ != std::nullopt;
  }
  if (result_is_available) {
    if constexpr (std::is_same_v<TCont, void>) {
      call_listener(listener);
      return create_finished_task();
    } else {
      if constexpr (is_task_impl<TCont>()) {
        return call_listener(listener);
      } else {
        auto result = call_listener(listener);
        return create_finished_task(result);
      }
    }
  } else {
    auto task = make_task<real_cont_type>();
    data->listeners_.push_back(std::bind([=]() mutable {
      if constexpr (std::is_same_v<TCont, void>) {
        call_listener(listener);
        task->set_result();
      } else {
        if constexpr (is_task_impl<TCont>()) {
          if constexpr (std::is_same_v<typename TCont::element_type::value_type,
                                       void>) {
            call_listener(listener)->then([=] { task->set_result(); });
          } else {
            call_listener(listener)->then(
              [=](auto value) { task->set_result(value); });
          }
        } else {
          auto result = call_listener(listener);
          task->set_result(result);
        }
      }
    }));
    return task;
  }
}

template <>
class task_impl<void> : public task_impl_tag {
public:
  struct Data {
    bool                               result_ = false;
    std::vector<std::function<void()>> listeners_;
  };

  using value_type = void;
  void set_result() {
    assert(not data->result_);
    data->result_ = true;
    std::vector<std::function<void()>> listeners;
    swap(listeners, data->listeners_);
    get_current_executor().add_work([listeners] {
      for (auto&& listener : listeners) {
        listener();
      }
    });
  }

  template <typename Fn>
  auto then(Fn&& listener) {
    return then_impl<void, decltype(listener())>(this, listener);
  }

private:
  friend class then_impl_accessor;
  std::shared_ptr<Data> data = std::make_shared<Data>();
};

template <typename T>
class task_impl : public task_impl_tag {
public:
  struct Data {
    std::optional<T>                    result_;
    std::vector<std::function<void(T)>> listeners_;
  };

  using value_type = T;
  void set_result(T result) {
    assert(data->result_ == std::nullopt);
    data->result_ = result;
    std::vector<std::function<void(T)>> listeners;
    swap(listeners, data->listeners_);
    get_current_executor().add_work([listeners, result] {
      for (auto&& listener : listeners) {
        listener(result);
      }
    });
  }

  template <typename Fn>
  auto then(Fn&& listener) {
    return then_impl<T, decltype(listener(*data->result_))>(this, listener);
  }

private:
  friend class then_impl_accessor;
  std::shared_ptr<Data> data = std::make_shared<Data>();
};

template <typename... Futures>
using combined_task_tuple
  = std::tuple<typename Futures::element_type::value_type...>;

template <typename... Futures>
using combined_task = task<combined_task_tuple<Futures...>>;
}

template <typename T>
using task = impl::task<T>;

template <typename T>
task<T> make_task() {
  return std::make_shared<impl::task_impl<T>>();
}

template <typename T>
task<T> create_finished_task(T result) {
  auto task = make_task<T>();
  task->set_result(result);
  return task;
}

inline task<void> create_finished_task() {
  auto task = make_task<void>();
  task->set_result();
  return task;
}

static_assert(
  std::is_same_v<impl::combined_task<task<int>>, task<std::tuple<int>>>);
static_assert(std::is_same_v<impl::combined_task<task<int>, task<double>>,
                             task<std::tuple<int, double>>>);

namespace impl {
template <std::size_t I,
          typename TaskTuple,
          typename ResultTuple,
          typename FinalTask>
void extract_task_result(TaskTuple                 tuple,
                         ResultTuple               result_tuple,
                         std::shared_ptr<uint32_t> counter,
                         FinalTask                 final_task) {
  std::get<I>(tuple)->then([result_tuple, counter, final_task](auto result) {
    std::get<I>(*result_tuple) = result;
    --(*counter);
    if (*counter == 0) {
      final_task->set_result(*result_tuple);
    }
  });
}
template <typename TaskTuple,
          typename ResultTuple,
          typename FinalTask,
          std::size_t... I>
void extract_task_results(TaskTuple                 tuple,
                          ResultTuple               result_tuple,
                          std::shared_ptr<uint32_t> counter,
                          FinalTask                 final_task,
                          std::index_sequence<I...> seq) {
  (void)seq;
  (extract_task_result<I>(tuple, result_tuple, counter, final_task), ...);
}
}

template <typename... Futures>
std::enable_if_t<(... && impl::is_task_impl<Futures>()),
                 impl::combined_task<Futures...>>
when_all(Futures... tasks) {
  using Result    = impl::combined_task_tuple<Futures...>;
  auto final_task = make_task<Result>();

  impl::extract_task_results(std::make_tuple(tasks...),
                             std::make_shared<Result>(),
                             std::make_shared<uint32_t>(sizeof...(tasks)),
                             final_task,
                             std::make_index_sequence<sizeof...(Futures)>{});

  return final_task;
}

template <typename Iterator>
typename std::enable_if<
  not impl::is_task_impl<Iterator>(),
  task<std::vector<typename Iterator::value_type::element_type::value_type>>>::
  type
  when_all(Iterator begin_it, Iterator end_it) {
  using ResultType
    = std::vector<typename Iterator::value_type::element_type::value_type>;
  auto final_task = make_task<std::decay_t<ResultType>>();

  const auto size          = std::distance(begin_it, end_it);
  auto       counter       = std::make_shared<uint32_t>(size);
  auto       result_holder = std::make_shared<ResultType>(size);
  size_t     index         = 0;
  for (auto it = begin_it; it != end_it; ++it) {
    (*it)->then([=](auto element) {
      (*result_holder)[index] = element;
      --(*counter);
      if (*counter == 0) {
        final_task->set_result(*result_holder);
      }
    });
    ++index;
  }
  return final_task;
}
