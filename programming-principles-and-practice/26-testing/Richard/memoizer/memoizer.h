#pragma once

#include <functional>

template <typename T>
class Memoizer {
    public:
        Memoizer(std::function<T()> fn) {
            myFn = fn;
        }
        auto get_value() {
            if ( ! cached ) {
                cachedResult = myFn();
                cached = true;
            }
            return cachedResult;
        }
    private:
        std::function<T()> myFn;
        bool cached = false;
        T cachedResult;

};
