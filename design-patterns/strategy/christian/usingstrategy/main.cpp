#include<iostream>

class FlyBehavior
{
public:
  virtual void fly() const = 0; 
};


class FlyWithWings : public FlyBehavior
{
public:
  FlyWithWings(){};
  void fly() const{
    std::cout << "flap-flap-flap" << std::endl; 
  }
};

class FlyNoWay : public FlyBehavior
{
public:
  FlyNoWay(){};
  void fly() const{
    std::cout << "................" << std::endl; 
  }
};


class Duck
{
public:
  FlyBehavior* flymode; 
  void performFly() const {
    flymode->fly(); 
  }
  virtual void display() = 0; 
  void quack(){
    std::cout << "Quaaaaaaaaack!" << std::endl; 
  }
};


class RedheadDuck : public Duck
// Rotkopfente
{
public:
  RedheadDuck(){
    flymode = new FlyWithWings; 
  } 
  void display(){
    std::cout << "I am a redhead duck." << std::endl; 
  }
};

class MallardDuck : public Duck{
// Stockente
public:
  MallardDuck(){
    flymode = new FlyWithWings; 
  } 
  void display(){
    std::cout << "I am a mallard duck." << std::endl; 
  }
};


class RubberDuck : public Duck{
public:
  RubberDuck(){
    flymode = new FlyNoWay; 
  };  

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

  
  RubberDuck duck2;
  duck2.display();
  duck2.performFly();
  duck2.quack(); 
  
  return 0;
}
