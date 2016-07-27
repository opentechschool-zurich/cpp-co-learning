#include <iostream>

class Coffee
{
    public:
        void print() const {std::cout << "Coffee!" << std::endl;}
};

template <class T>
class CreamDecorator
{
    public:
        CreamDecorator(const T &x) : nested(x) {}
        void print() const {nested.print(); std::cout << "... with cream." << std::endl;}
    private:
        const T& nested;
};

template <class T>
class SugarDecorator
{
    public:
        SugarDecorator(const T& x) : nested(x) {}
        void print() const {nested.print(); std::cout << "... with sugar." << std::endl;}
    private:
        const T& nested;
};

template <class T>
CreamDecorator<T> addCream(const T& x) {return CreamDecorator<T>(x);}

template <class T>
SugarDecorator<T> addSugar(const T& x) {return SugarDecorator<T>(x);}
