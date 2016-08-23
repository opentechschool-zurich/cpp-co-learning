#include <iostream>
#include <random>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <mutex>


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
    void set_number(int i){
      number = i; 
    }
    int number; 
  };
  

  std::mutex access_from_above;
  std::mutex access_from_below;


  class Guard {
  public:
    explicit Guard(std::mutex& m): m{m} {m.lock();}
    ~Guard() {m.unlock();}
  private:
    std::mutex& m;
  };


  class Escalator
  {
  public:
    void stepOn(Person p){
      cout << "Person "<< p.number <<" steps on." << endl;
      if(nPersons==0){
	d = p.m_d;
	if (d == Direction::up)
	  cout << "Escalator going up now..."; 
	else
	  cout << "Escalator going down now..."; 
      }
      else{
	if (p.m_d != d) {
	  cout << "Person stumbling in opp direction." << endl;
	}
      }
      nPersons++;
      cout << "with " << nPersons << endl; 
      usleep(400000);
    }

    void changedir(){
      Guard g(dir_mutex); 
    }

    void stepOff(Person p){
      cout << "Person " << p.number << " steps off" << endl;
      nPersons--;
    }
    Direction d = Direction::up;
  private:
    int nPersons{0};
    std::mutex dir_mutex;
  };


  // namespace-global instance of our escalator
  Escalator e;

  

  /**
   * Makes a Person with a random Direction
   */
  int PersonNumber = 0;
  
  Person makePerson() {
    Person p = boolDist(eng) ? Person(Direction::up) : Person(Direction::down);
    PersonNumber++; 
    p.set_number(PersonNumber); 
    return p; 
  }

  /**
   *  Function to be run from withing a thread
   */
  void personSteppingOnEscalator() {
    Person  newperson = makePerson();

    if (newperson.m_d == e.d) {
      e.stepOn( newperson );
    }
    else {
      e.changedir(); 
      e.stepOn( newperson );
    }
    e.stepOff( newperson);
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
