#include "task.h"

namespace detail {
Executor*& get_current_executor_holder() {
  static thread_local Executor* executor;
  return executor;
}
}
