// main.cpp: decorating pattern as in head first design patterns book
#include<iostream>
#include<string>

using namespace std; 

class Component
{
public:
  virtual string getDescription(){
    return description;
  };

  virtual double calculate_cost(){
    return 0; 
  }; 
  
protected:
  string description{"Unknown Beverage"}; 

};

class CondimentDecorator : public Component
{
public:
  virtual string getDescription() = 0; 
};


class Espresso : public Component
{
public:
  Espresso(){
    description = "Espresso"; 
  };
  virtual double calculate_cost(){ return 0.80; }; 
};


class Milk : public CondimentDecorator
{
public:
  Milk(Component* beverage)
    : m_beverage{beverage}{}; 

  string getDescription(){
    return m_beverage.getDescription() + " Macchiato"; 
  }

  double calculate_cost(){
    return 0.20 + m_beverage.calculate_cost(); 
  }; 

protected:
  Component m_beverage; 
};


class Sugar : public CondimentDecorator
{
public:
  Sugar(Component& beverage)
    : m_beverage{beverage}{}; 

  string getDescription(){
    return m_beverage.getDescription() + " with sugar"; 
  }

  double calculate_cost(){
    return 0.50 + m_beverage.calculate_cost(); 
  }; 

protected:
  Component m_beverage; 
};


int main()
{
  Espresso coffee; 

  Component* LucasDrink = &coffee;
  cout << "Luca drinks a " << LucasDrink->getDescription()
       << " and pays " << LucasDrink->calculate_cost() << endl;

  
  
  Component* DelfDrink = &coffee;
  DelfDrink = Milk(DelfDrink);
  
  cout << "Delf drinks a " << DelfDrink.getDescription()
       << " and pays " << DelfDrink.calculate_cost() << endl;
  

  return 0;
}

