#include <iostream>
#include <vector>
#include <functional>

class D
{
public:
    void add(std::function<int(int)> f)
    {
        std::cout << ">>" << std::endl;
        d.push_back(f);
    }
    void go()
    {
        std::cout << "<<" << std::endl;
        for(auto fn : d)
            std::cout << "::" << fn(e) << std::endl;
    }
private:
    int e = 4;
    std::vector<std::function<int(int)>> d = {};
};

class Abc
{
public:
    Abc(D& d): d{d}
    {
        auto aLambda = [this](int a) { return b(a); };
        d.add(aLambda);
        auto bLambda = [this](int a) { return c(a); };
        d.add(bLambda);
        
    }
    int b(int i) {return a * i;}
    int c(int i) {return a + i;}
private:
    int a = 2;
    D d;
};

int main()
{
    D d;
    Abc a(d);
    d.go();
}
