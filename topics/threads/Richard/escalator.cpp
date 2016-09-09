#include <chrono>
#include <condition_variable> // std::condition_variable
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

namespace {

std::mt19937_64 eng{std::random_device{}()}; // or seed however you want

void sleepRandomTime() {
  static std::uniform_int_distribution<> distribution{5, 80};
  std::this_thread::sleep_for(std::chrono::milliseconds{distribution(eng)});
}

enum class Direction { up, down, idle };

/**
* returns a description for the Direction enum*/
auto getDirectonString(Direction d) -> string {
  if (d == Direction::up)
    return "up";
  else if (d == Direction::down)
    return "down";
  else
    return "idle";
}

/**
* Person class that holds the direction the person intents to travel on the
* escalator
*/
class Person {
public:
  Person(Direction intendedDirection)
      : intendedDirection{intendedDirection}, number(++totalPersons){};
  Direction intendedDirection;
  int number;              // the unique number of the Person
  static int totalPersons; // how many People created so far

  /**
  * returns a string of tabs that allows the person output to be indented by
  * the member var number to facilitate understanding of which thread is
  * doing what.
  */
  auto tabs(void) -> string {
    stringstream s;
    for (int i = 1; i < number; ++i)
      s << "\t";
    return s.str();
  }

  /**
  * describes the person's intent
  */
  auto describe() -> void {
    stringstream s;
    s << tabs() << "Person " << number << " wants to ride the escalator "
      << getDirectonString(intendedDirection) << endl;
    cout << s.str();
  }
private:

};

// static initialiser (Can't be initialized in the class)
int Person::totalPersons = 0;

/**
 * Makes a Person with a random Direction
 */
auto makeRandomPerson() -> Person {
  static std::uniform_int_distribution<> boolDist{0, 1};
  Person p = boolDist(eng) ? Person(Direction::up) : Person(Direction::down);
  return p;
};

class Escalator {
public:
  std::mutex mtx;
  std::condition_variable cv;

  /**
  * any thread can request a person to ride the escalator
  */
  auto ride(Person p) -> void {
    p.describe();

    { // RAII block to ensure the lock is unlocked event when an exception
      // occurs
      std::unique_lock<std::mutex> lck(mtx);
      cv.wait(lck, [this, p] {
        return (nPersons < 3 && escalatorDirection == p.intendedDirection) ||
               nPersons == 0;
      });
      hopOn(p);
      cv.notify_all(); // other threads might be waiting for the changed
                       // direction
    }
    usleep(800000);

    { // RAII block
      std::unique_lock<std::mutex> lck(mtx);
      stepOff(p);
      cv.notify_all(); // others might now want to hopOn
    }
  }

  auto printEscalatorState(string tabs) -> void {
    string direction = escalatorDirection == Direction::up ? "up" : "down";
    stringstream s;
    s << tabs << "Escalator going " << getDirectonString(escalatorDirection)
      << " with " << nPersons << " aboard.\n";
    cout << s.str();
  }

private:
  int nPersons{0};
  Direction escalatorDirection = Direction::idle;

  auto hopOn(Person p) -> void {
    stringstream s;
    s << p.tabs() << "Person " << p.number << " hops on the escalator\n";
    cout << s.str();

    if (nPersons == 0 && p.intendedDirection != escalatorDirection) {
      stringstream change;
      change << p.tabs() << "Person " << p.number
             << " is changing the direction from "
             << getDirectonString(escalatorDirection) << " to "
             << getDirectonString(p.intendedDirection) << endl;
      cout << change.str();
      escalatorDirection = p.intendedDirection;
    }

    if (p.intendedDirection != escalatorDirection) {
      stringstream fall;
      fall << p.tabs() << "Person " << p.number << " falls and hurts themself."
           << endl;
      cout << fall.str();
    }
    nPersons++;
    printEscalatorState(p.tabs());
  }

  auto stepOff(Person p) -> void {
    stringstream s;
    s << p.tabs() << "Person " << p.number << " steps off the escalator "
      << endl;
    cout << s.str();
    nPersons--;
    printEscalatorState(p.tabs());
  }
};

// namespace-global instance of our escalator
Escalator e;

/**
 *  Function to be run from within a thread
 */
void personThread() {
  Person newperson = makeRandomPerson();
  e.ride(newperson);
}

class Producer {
public:
  Producer() {
    thread producerThread(&Producer::producePeopleThreads, this);
    producerThread.join();
  }

private:
  void producePeopleThreads() {
    e.printEscalatorState("");
    for (int i = 1; i < 10; ++i) {
      thread t(&personThread);
      t.detach();
      this_thread::sleep_until(chrono::system_clock::now() +
                               chrono::milliseconds(200));
    }
  }
};

} // anonymous namespace

int main() {
  Producer producer{};
  usleep(10000000);
  cout << "Time ran out.\n";
}
