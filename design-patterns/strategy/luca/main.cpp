#include<iostream>

class FlyBehavior
{
public:
  virtual void fly() const = 0; 
};


class FlyWithWings : public FlyBehavior
{
public:
  FlyWithWings(){}
  virtual void fly() const{
    std::cout << "flap-flap-flap";
  }
};

class FlyNoWay : public FlyBehavior
{
public:
  FlyNoWay(){}
  virtual void fly() const{
    std::cout << "................";
  }
};

class QuackBehavior
{
protected:
    double volume;

public:
    explicit QuackBehavior (double vol) : volume{vol} {}

    virtual void quack() const = 0;
};

class DoubleQuack : public QuackBehavior
{
public:
    DoubleQuack() : QuackBehavior(42.0) {}
    virtual void quack() const
    {
        std::cout << "quack quack .. twice!";
    }
};

class SqueakQuack : public QuackBehavior
{
public:
    SqueakQuack() : QuackBehavior(30.5) {}
    virtual void quack() const
    {
        std::cout << "squeak!";
    }
};




class Duck
{
public:
  void performFly() const {
    flymode->fly();
    std::cout << std::endl;
  }
  virtual void display() = 0; 

  void performQuack(){
    quackmode->quack();
    std::cout << std::endl;
  }

protected:
  FlyBehavior* flymode;
  QuackBehavior* quackmode;

};


class RedheadDuck : public Duck
// Rotkopfente
{
private:
    FlyWithWings myFlyMode;
    DoubleQuack myQuackMode;

public:
  RedheadDuck(){
    flymode = &myFlyMode;
    quackmode = &myQuackMode;
  } 
  void display(){
    std::cout << "I am a redhead duck." << std::endl; 
  }
};

class MallardDuck : public Duck{
// Stockente
private:
    FlyWithWings myflyMode;
    DoubleQuack myQuackMode;

public:
  MallardDuck(){
    flymode = &myflyMode;
    quackmode = &myQuackMode;
  } 
  void display(){
    std::cout << "I am a mallard duck." << std::endl; 
  }
};


class RubberDuck : public Duck{
private:
    FlyNoWay myFlymode;
    SqueakQuack myQuackMode;

public:
  RubberDuck(){
    flymode = &myFlymode;
    quackmode = &myQuackMode;
  }

  void display(){
    std::cout << "I am a rubber duck." << std::endl; 
  }
};



int main(){
  std::cout << "Where are the duckies?"
            << std::endl << std::endl; 
  
  RedheadDuck duck1;
  duck1.display();
  duck1.performFly();
  duck1.performQuack();

  
  RubberDuck duck2;
  duck2.display();
  duck2.performFly();
  duck2.performQuack();
  
  return 0;
}
