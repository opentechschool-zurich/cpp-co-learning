#include <iostream> 

class C {
    public:
        virtual void bar() const = 0;
        virtual ~C() {};
};

class D: public C {
    public:
        void bar() const {
            std::cout << "behave" << std::endl;
        }
};

class A {
    C* c;
    public:
    A(C* c) : c(c) {}

    virtual ~A() {
        delete c;
    }
    void foo() {
        c->bar();
    }
};

class B: public A {
    public:
        B() : A(new D) {}
};

int main() {
    B b;
    b.foo();
    return 0;
}

