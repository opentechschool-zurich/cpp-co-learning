#include <iostream>
#include <map>
#include <tuple>
#include <functional>

#include <chrono>
#include <thread>

template <typename R, typename... Args>
std::function<R (Args...)> memo(R (*fn)(Args...))
{
    std::map<std::tuple<Args...>, R> table;
    return [fn, table](Args...args) mutable -> R {
        auto argt = std::make_tuple(args...);
        auto memoized = table.find(argt);
        if (memoized == table.end()) {
            auto result = fn(args...);
            table[argt] = result;
            return result;
        } else {
            return memoized->second;
        }
    };
}

int identity(int a) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return a;
}

int main()
{
    auto s = memo<int, int>(identity);
    std::cout << s(10) << std::endl;
    std::cout << s(20) << std::endl;
    std::cout << s(10) << std::endl;
}
