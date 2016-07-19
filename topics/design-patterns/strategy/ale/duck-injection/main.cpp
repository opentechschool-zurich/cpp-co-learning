#include <iostream>

class QuackBehavior
{
public:
    virtual void quack() const = 0;
    virtual ~QuackBehavior() {};
    virtual QuackBehavior* clone() const = 0;
};

class QuackQuacking : public QuackBehavior
{
public:
    void quack() const {
        std::cout << "quack" << std::endl;
    }
    QuackQuacking* clone() const {
        return new QuackQuacking(*this);
    }
};

class QuackSqueaking : public QuackBehavior
{
public:
    QuackSqueaking* clone() const {
        return new QuackSqueaking(*this);
    }
    void quack() const {
        std::cout << "squeek" << std::endl;
    }
};

class Duck
{
public:
    QuackBehavior* quackBehavior;
    Duck(QuackBehavior* quackBehavior) : quackBehavior{quackBehavior} {}
    virtual ~Duck() {
        delete quackBehavior;
    };
    // copy constructor

    Duck(const Duck& copy) :
        quackBehavior(copy.quackBehavior->clone())
    {
    }

    void setQuackBehavior(QuackBehavior* qb) {
        quackBehavior = qb;
    };

    void quack() {
        quackBehavior->quack();
    };
};

class RedheadDuck : public Duck {
public:
    RedheadDuck() : Duck(new QuackQuacking) {};
};

int main()
{

    RedheadDuck duck;
    duck.quack();

    RedheadDuck duck2 = duck;
    duck2.quack();
    duck2.setQuackBehavior(new QuackSqueaking);
    duck2.quack();
    duck.quack();

}
