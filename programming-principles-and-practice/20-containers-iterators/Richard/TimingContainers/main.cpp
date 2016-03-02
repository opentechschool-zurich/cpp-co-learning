#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>

using namespace std;
using namespace chrono;


/**
* This function receives a container and inserts "howMany"
* random numbers in the range of 0..RAND_MAX to the container.
* Since we want to test the preformance of the insert method
* we locate the numerically ascending insertion point and
* insert the random number there.
*/
template<typename ContainerT>
void insertRandomNumbers( ContainerT container, int howMany ) {
    //list<int> dummyVector;
    for (int j = 0; j < howMany; j++) {
      int myRandom = rand();
      auto insertionPoint = upper_bound (container.begin(), container.end(), myRandom);
      container.insert( insertionPoint, myRandom);
    }
}


/**
* This function creates a vector "cycles" times and then
* calls insertRandomNumbers with the size paramerter to fill
* it up. It outputs the execution time in milliseconds
*/
template<typename ContainerT>
void timeAContainer( ContainerT container, int cycles, int size, string containerType ) {
    auto startTime = system_clock::now();
    for (int i=0; i<cycles; ++i) {
        insertRandomNumbers(container, size);
    }
    auto endTime = system_clock::now();
    auto ms = duration_cast<milliseconds>( (endTime - startTime) / cycles).count();
    cout << "timeAContainer of type "<< containerType << " with " << size << " elements ran << "
    << ms << "ms per cycle (" << cycles << " cycles)\n";
}


int main() {
    srand (time(NULL));

    vector<int> cycles   {10,  10,    4,     2,     1,      1,      1,      1};
    vector<int> elements {10, 100, 1000, 10000, 50000, 100000, 200000, 500000};

    for ( int i=0; i < elements.size(); ++i ) {
        {
            vector<int> myVector;
            timeAContainer(myVector, cycles[i], elements[i], "vector<int>");
        } // putting this in a block so that the memory is freed
        {
            list<int> myList;
            timeAContainer(myList, cycles[i], elements[i], "list<int>  ");
        }
    }
}
