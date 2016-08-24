#include <iostream>
#include <random>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <boost/thread.hpp>
#include <string>
#include <sstream>

using namespace std;

namespace {

  std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
  std::uniform_int_distribution<> dist{5, 80};
  std::uniform_int_distribution<> boolDist{0, 1};

  void sleepRandomTime() {
    std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
  }

  enum class Direction {up, down};

  class Person  {
  public:
    Person(Direction d): m_d{d} , number(++PersonNumber){
        //PersonNumber++;
        //number = PersonNumber;
        //number = 1;
    };
    Direction m_d;
    int number;
    static int PersonNumber;

    auto tabs(void) -> string {
        std::stringstream ss;
        for ( int i = 0; i < number; ++i)
            ss << "\t";
        return ss.str();
    }
  };

  int Person::PersonNumber=0;

  class Escalator  {
  public:
      Direction d = Direction::up;
      auto ride(Person p) -> void {
            string direction = p.m_d == Direction::up ? "up" : "down";
            cout << p.tabs() << "Person "  << p.number << " wants to ride the escalator " << direction << endl;
            if ( p.m_d != d ) {
                cout << p.tabs() <<"We need to change the direction of the elevator\n";
                //boost::upgrade_lock<boost::shared_mutex> lock(escalator_moving);
                //boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(escalator_moving);
                boost::unique_lock< boost::shared_mutex > lock(escalator_moving);
                cout << p.tabs() <<"Person "  << p.number << " changed the direction to " << direction << endl;
                d = p.m_d;
            }
            boost::shared_lock<boost::shared_mutex> lock( escalator_moving );
            cout << p.tabs() <<"Person "  << p.number << " hops on the escalator\n" ;
            if (p.m_d != d) {
	             cout << p.tabs() <<"Person " << p.number << " stumbling in opp direction." << endl;
	        }
            nPersons++;
            print_escalator_state(p.tabs());
            usleep(800000);
            cout << p.tabs() <<"Person "  << p.number << " steps off the escalator " << endl;
            nPersons--;
            print_escalator_state(p.tabs());
            //cout << p.tabs() <<"Person "  << p.number << " shared lock going out of scope" << endl;
        }


    auto print_escalator_state( string tabs ) -> void {
        string direction = d == Direction::up ? "up" : "down";
        cout << tabs << "Escalator going " << direction  << " with " << nPersons << " aboard.\n";
    }
  private:
    int nPersons{0};
    boost::shared_mutex escalator_moving;
  };



  // namespace-global instance of our escalator
  Escalator e;



  /**
   * Makes a Person with a random Direction
   */
  Person makePerson() {
    Person p = boolDist(eng) ? Person(Direction::up) : Person(Direction::down);

    return p;
  }

  /**
   *  Function to be run from withing a thread
   */
  void personSteppingOnEscalator() {
    Person  newperson = makePerson();
    e.ride( newperson );
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
