// http://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function
#include <stdio.h>
#include <functional>

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args> 
    static Ret callback(Args... args) {                    
        return func(args...);  
    }
    static std::function<Ret(Params...)> func; 
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

void register_with_library(int (*func)(int *k, int *e)) {
    int x = 0, y = 1;
    int o = func(&x, &y);
    printf("Value: %i\n", o);
}

class A {
    public:
        A();
        ~A();
        int e(int *k, int *j);
    private:
        int b = 2;
};

typedef int (*callback_t)(int*,int*);

A::A() {
    Callback<int(int*,int*)>::func = std::bind(&A::e, this, std::placeholders::_1, std::placeholders::_2);
    callback_t func = static_cast<callback_t>(Callback<int(int*,int*)>::callback);      
    register_with_library(func);      
}

int A::e(int *k, int *j) {
    return b*(*k - *j);
}

A::~A() { }

int main() {
    A a;
}
