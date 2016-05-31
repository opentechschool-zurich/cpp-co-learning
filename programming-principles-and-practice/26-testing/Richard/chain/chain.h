#pragma once

#include <functional>
// receive 2 functions T1, T2
template <typename T1, typename T2>
// return a lambda function (don't care about type--> auto) C++14 only
//auto chain(T1 fn1, T2 fn2) {

// C++11 version
std::function<void()> chain(T1 fn1, T2 fn2) {
    return [fn1, fn2]()
        {
            // function body call the two functions one after the other
            fn1();
            fn2();
         };
}
