#include <thread>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void sleepRandomTime() {
  std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
  std::uniform_int_distribution<> dist{5, 80};
  std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
}

enum class Direction{
  up, down 
};

class Person
{
public:
  Person(Direction d): m_d{d}{};
  Direction m_d;
};

class Escalator
{
public:
  void stepOn(Person p){
    cout << "Person steps on." << endl;
    if(nPersons==0){
      d = p.m_d;
      if (d == Direction::up)  
	cout << "Escalator going up now..." << endl;
      else
	cout << "Escalator going down now..." << endl;
    }
    else{
      if (p.m_d != d) {
	cout << "Person falling off the elevator ... ahhhhhh" << endl; 
      }
    }
    nPersons++; 
  }
  void stepOff(){
    cout << "Person steps off" << endl;
    nPersons--; 
  }

private:
  int nPersons{0}; 
  Direction d; 
};


int main() {
  Escalator e;
  Person p1(Direction::up);
  e.stepOn(p1);
  Person p2(Direction::down);
  e.stepOn(p2); 

  Person p3(Direction::up);
  e.stepOn(p3);

  // std::thread t1(YesFunction);
  // std::thread t2(NoFunction);
  // t1.join();
  // t2.join();
}
