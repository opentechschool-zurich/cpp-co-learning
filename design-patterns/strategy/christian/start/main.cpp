#include<iostream>


using namespace std;

class Duck
{
public:
  Duck(){};
  virtual void display() const = 0;
};



class RedheadDuck : public Duck
{
public:
  virtual void display(){
    std::cout << "I am a redhead duck." << endl; 
  }
};





int main()
{
  
  RedheadDuck duck1;
  duck1.display();
  


  

  return 0;
}
