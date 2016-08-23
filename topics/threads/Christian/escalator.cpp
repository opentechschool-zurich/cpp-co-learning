#include <thread>
#include <iostream>
#include <random>
#include <chrono>
#include <unistd.h>

using namespace std;

namespace {

std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
std::uniform_int_distribution<> dist{5, 80};
std::uniform_int_distribution<> boolDist{0, 1};

void sleepRandomTime() {
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


// namespace-global instance of our escalator
Escalator e;


/**
* Makes a Person with a random Direction
*/
Person makePerson() {
    return boolDist(eng) ? Person(Direction::up) : Person(Direction::down);
}

/**
*  Function to be run from withing a thread
*/
void personSteppingOnEscalator() {
    e.stepOn( makePerson() );
}

class Producer {
public:
    Producer() {
        thread producerThread(&Producer::producePeople, this);
        producerThread.detach();
    }
private:
    void producePeople() {
        for ( int i=1; i<10; ++i ) {
            thread t(&personSteppingOnEscalator);
            t.detach();
            this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(200));
        }
        cout << "Finished producing People\n";
    }
};

} // anonymous namespace

int main() {
  Producer producer {};
  usleep(10000000);
  cout << "Time ran out.\n";
}
