#include <iostream>
 
template <typename QuackPolicy, typename FlyPolicy>
class Duck : private QuackPolicy, private FlyPolicy
{
    using QuackPolicy::quack;
    using FlyPolicy::fly;
 
public:
    // Behaviour method
    void performQuack() const
    {
        quack();
    }
    void performFly() const
    {
        fly();
    }
};
 
class QuackPolicyQuack
{
protected:
    void quack() const
    {
        std::cout << "quack" << std::endl;
    }
};
 
class QuackPolicySqueek
{
protected:
    void quack() const
    {
        std::cout << "squeek" << std::endl;
    }
};
 
class FlyPolicyWithWings
{
protected:
    std::string fly() const
    {
        std::cout << "flap-flap-flap" << std::endl;
    }
};
 
class FlyPolicyNoWay
{
protected:
    std::string fly() const
    {
        std::cout << ".............." << std::endl;
    }
};
 
int main()
{
    typedef Duck<QuackPolicyQuack, FlyPolicyWithWings> RedheadDuck;
 
    RedheadDuck readheadDuck;
    readheadDuck.performFly();
    readheadDuck.performQuack();
 

    typedef Duck<QuackPolicySqueek, FlyPolicyNoWay> RubberDuck;
 
    RubberDuck rubberDuck;
    rubberDuck.performFly();
    rubberDuck.performQuack();
}
