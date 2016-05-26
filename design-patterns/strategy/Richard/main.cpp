#include<iostream>
#include<vector>

class FlyBehavior
{
public:
  virtual void fly() const = 0; 
};


class FlyWithWings : public FlyBehavior
{
public:
  FlyWithWings(){};
  virtual void fly() const{
    std::cout << "flap-flap-flap" << std::endl; 
  }
};

class FlyNoWay : public FlyBehavior
{
public:
  FlyNoWay(){};
  virtual void fly() const{
    std::cout << "................" << std::endl; 
  }
};

class RocketMotor : public FlyBehavior
{
public:
  
  virtual void fly() const{
    std::cout << "zooOOM!" << std::endl; 
  }
};

  
  
  
class Duck
{
public:
	// a virtual destructor
	virtual ~Duck(){
		std::cout << "running virtual destructor on class Duck" << std::endl;
  }
  void performFly() const {
    flymode->fly(); 
  }
  virtual void display() = 0; 
  void quack(){
    std::cout << "Quaaaaaaaaack!" << std::endl; 
  }
protected:
  FlyBehavior* flymode; 
};


class RedheadDuck : public Duck
// Rotkopfente
{
public:
  RedheadDuck(){
    flymode = new FlyWithWings(); 
  } 
  // destructor
  ~RedheadDuck() {
		std::cout << "running destructor on class RedheadDuck" << std::endl;
    delete flymode;
  }
  void display(){
    std::cout << "I am a redhead duck." << std::endl; 
  }
  void upgrade() {
    delete flymode;
    flymode = new RocketMotor();
  }
};

class MallardDuck : public Duck{
// Stockente
public:
  MallardDuck(){
    flymode = new FlyWithWings(); 
  } 
  // destructor
  ~MallardDuck() {
		std::cout << "running destructor on class MallardDuck" << std::endl;
    	delete flymode;
  }
  void display(){
    std::cout << "I am a mallard duck." << std::endl; 
  }
};


class RubberDuck : public Duck{
public:
  RubberDuck(){
    flymode = new FlyNoWay(); 
  };  
  // destructor
  ~RubberDuck() {
		std::cout << "running destructor on class RubberDuck" << std::endl;
    	delete flymode;
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
  std::cout << "Upgrading to RocketMotor" << std::endl;
  duck1.upgrade();
  duck1.performFly();

  
  RubberDuck duck2;
  duck2.display();
  duck2.performFly();
  duck2.quack(); 
  
  /* The below two lines seem reasonable to a Java programmer
   * but C++ is not Java. The answer lies in the fact that Duck
   * is an abstract class. The extending subclasses may have more
   * fields and functions and therefore the size of the ultimate
   * object is not known. So the compiler can't figure out how 
   * much memory to reserve per duck and therefore it is not allowed.
   * Instead we can create new ducks and add pointers to the ducks to
   * the vector.
   * @see http://stackoverflow.com/questions/2160920/why-cant-we-declare-a-stdvectorabstractclass
  std::vector<Duck> ducks;
  ducks.push_back(duck1);
  */
  
  std::cout << "Creating a vector of pointers to ducks..." << std::endl;
  
  std::vector<Duck*> ducks;
  ducks.push_back(&duck1);
  ducks.push_back(&duck2);

  std::cout << "Iterating over the ducks vector..." << std::endl;
  for ( auto ducky : ducks ) {
    std::cout << "Duck display: ";
    ducky->display();
    std::cout <<  "Duck quack: ";
    ducky->quack();
    std::cout << "Duck performFly: ";
    ducky->performFly();
    std::cout << std::endl;
  }
  
  
  return 0;
}
