#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <utility>

/*

  Queue count flow example

  Luca  : 1
  Luca  : 2
  Katrin: 1
  Luca  : 3
  ..
  ..
  Luca  : 5
  Katrin: 10
  Luca  : 7


*/

typedef std::pair<std::string, int> queueElement;
typedef std::queue< queueElement  > queueType;

class Counter {

    std::string name;
    std::string otherName;
    int value;
    int step;
    queueType &queue;

public:
    Counter (const std::string &name, const std::string &other,
             queueType &queue
             )
        : name(name), otherName(other), value(0), step(1), queue(queue)
    { }


    int count()
    {
        queueElement e;

        if ( ! queue.empty() ) {
            e = queue.front();
            if (e.first == name) {
                step = e.second;
                queue.pop();
            }
        }

        //int olderValue = oldValue;
        int oldValue = value;
        value += step;
        std::cout << name << ": " << value << std::endl;

        if (value == 10) {
            queue.push(std::make_pair(otherName, 4));
            value = 0;
            iPushed();

        }else if (value % 20 == 0) {
            queue.push(std::make_pair(otherName, 0));
            value = 0;
            iPushed();

        }else if (value == oldValue) {
            queue.push(std::make_pair(otherName, -1));
            iPushed();

        }else if (value < -5) {
            queue.push(std::make_pair(otherName, 0));
            value = 0;
            iPushed();
        }


        return value;
    }

    void iPushed()
    {
        std::cout << name << " push to queue" << std::endl;
    }

};

int main () {

    queueType realQueue;


    Counter cnt1("Luca", "Katrin", realQueue);
    cnt1.count();
    cnt1.count();

    Counter cnt2("Katrin", "Luca", realQueue);
    cnt2.count();

    for ( int i = 0; i<40; i++) {
        cnt1.count();
        cnt2.count();
    }

    std::cout << "Queue contents at the end:" << std::endl;


    while ( ! realQueue.empty() )
    {
        auto i = realQueue.front();

        std::cout << i.first << ": " << i.second << std::endl;

        realQueue.pop();

    }

}
