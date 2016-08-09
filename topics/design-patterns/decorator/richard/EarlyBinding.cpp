// EarlyBinding.cpp
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class FooBar {
public:
    virtual void doSomething() {
        std::cout << "FooBar\n";
    }
};

class Foo : public FooBar {
public:
    void doSomething() override {
        std::cout << "Foo\n";
    }
};

class Bar : public FooBar {
public:
    void doSomething() override {
        std::cout << "Bar\n";
    }
};

int main() {
    Foo f;
    Bar b;
    FooBar fb;
    srand(time(NULL));
    for (auto i = 1; i <= 10; ++i) {
        auto r = rand() % 10 + 1;
        if (r > 5)
            fb = f;
        else
            fb = b;
        fb.doSomething();
    }
    return 0;
}
