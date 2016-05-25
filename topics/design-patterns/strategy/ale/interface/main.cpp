#include<iostream>
#include<string>

class Anything
{
public:
    virtual void say() {std::cout << "I could be anything" << std::endl;}
};

class Something: public Anything
{
public:
    std::string whatIAm{"I'm something"};
    void say() {std::cout << whatIAm << std::endl;}

};

class SomethingElse: public Anything
{
public:
    std::string whatIAm{"I'm something else"};
    void say() {std::cout << whatIAm << std::endl;}

};

class Base
{
public:
    ~Base() {std::cout << "~base" << std::endl; delete anything;};
protected:
    Anything* anything;
    void virtual say() = 0;
};

class Derived: public Base
{
public:
    Derived() {anything = new Something();};
    // ~Derived() {std::cout << "~derived" << std::endl; /*delete anything;*/};

    void say() {anything->say();}
};


int main(){
  Derived derived;
  derived.say();

  Derived rederived;
  rederived.say();
}
