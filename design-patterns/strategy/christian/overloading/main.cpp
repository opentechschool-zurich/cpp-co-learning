#include<iostream>


class Duck
{
public:
  virtual void display() = 0; 
  void fly(){
    std::cout << "flap-flap-flap" << std::endl; 
  }
  void quack(){
    std::cout << "Quaaaaaaaaack!" << std::endl; 
  }
};


class RedheadDuck : public Duck
// Rotkopfente
{
public:
  RedheadDuck(){}; 
  void display(){
    std::cout << "I am a redhead duck." << std::endl; 
  }
};

class MallardDuck : public Duck
// Stockente
{
public:
  MallardDuck();
  void display(){
    std::cout << "I am a mallard duck." << std::endl; 
  }
};




class RubberDuck : public Duck
{
public:
  RubberDuck(){}; 
  void display(){
    std::cout << "I am a rubber duck." << std::endl; 
  }
  void fly(){
    std::cout << "..............." << std::endl; 
  }
};



int main()
{
  
  RedheadDuck duck1;
  duck1.display();
  duck1.fly();

  
  RubberDuck duck2;
  duck2.display();
  duck2.fly();
  duck2.quack(); 
  
  return 0;
}
