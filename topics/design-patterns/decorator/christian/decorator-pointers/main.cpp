// main.cpp: decorating pattern as in head first design patterns book
#include<iostream>
#include<string>
#include<memory>

using namespace std; 


class Component
{
public:
  virtual string getDescription(){
    return description;
  };

  virtual double calculate_cost() = 0; 
  
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
    cout << "Making fine espresso" << endl; 
    description = "Espresso"; 
  };
  virtual double calculate_cost(){ return 0.80; }; 
  ~Espresso(){cout << "Destroying espresso" << endl;}

  Espresso(const Espresso& e){
    cout << "Espresso copying ..." << endl; 
    description = e.description; 
  }

  

};


class Milk : public CondimentDecorator
{
public:
  Milk(shared_ptr<Component> beverage)
    : m_beverage{beverage}{}; 

  string getDescription(){
    return m_beverage->getDescription() + " Macchiato"; 
  }

  double calculate_cost(){
    return 0.20 + m_beverage->calculate_cost(); 
  }; 

protected:
  shared_ptr<Component> m_beverage; 
};


class Sugar : public CondimentDecorator
{
public:
  Sugar(Component* beverage)
    : m_beverage{beverage}{}; 

  string getDescription(){
    return m_beverage->getDescription() + " with sugar"; 
  }

  double calculate_cost(){
    return 0.50 + m_beverage->calculate_cost(); 
  }; 

protected:
  Component* m_beverage; 
};

// class Beverage
// // class Beverage holds a pointer to a concret component 
// {
// public:
//   Beverage(Component::* p){
//     m_beverage = new (Component.*p)();    
//   }

//   virtual ~Beverage(){
//     delete m_beverage;
//   }

// private:
//   Component* m_beverage;  
// };


int main(){
  
  // Component* DelfDrink = new Espresso();
  // DelfDrink = new Milk(DelfDrink);

  //  cout << "Delf drinks a " << DelfDrink->getDescription()
  //       << " and pays " << DelfDrink->calculate_cost() << endl;

  //  shared_ptr<Component> DelfDrink = make_shared<Espresso>(Espresso());
  shared_ptr<Component> DelfDrink = make_shared<Espresso>(Espresso());

  cout << "Delf drinks a " << DelfDrink->getDescription()
       << " and pays " << DelfDrink->calculate_cost() << endl;

  DelfDrink = make_shared<Milk>(Milk(DelfDrink)); 

  cout << "Delf drinks a " << DelfDrink->getDescription()
       << " and pays " << DelfDrink->calculate_cost() << endl;




  //  shared_ptr<Component> DelfDrink (Espresso()); 
    //Espresso DelfDrink = Espresso();



  //   DelfDrink =  Milk(DelfDrink); 
     
   //    cout << "Delf drinks a " << DelfDrink->getDescription()
  //       << " and pays " << DelfDrink->calculate_cost() << endl;



  
  return 0;
}

