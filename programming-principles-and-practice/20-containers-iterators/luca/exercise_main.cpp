#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;
using namespace chrono;

template<typename T>
void do_container(int n) {
    T myvect;
    
    for (int i = 0; i<n; i++) { // timing loop
        int myrand = rand() % n;

        // loop all the vector looking for the element to insert before it
        auto it = myvect.begin();
        for (; it!=myvect.end(); ++it) {
            if (*it > myrand) { // once found insert and exit the loop
                break;
            }
        }
        // when the vector is empty we have begin()=end() so insert before end() will do the trick
        // when the vector has an entry with a bigger value the iterator is at the correct position
        // when the vector has nothing with a bigger value then myrand we will fully loop the vector
        // // the iterator will be at end() and it is also good
        myvect.insert(it, myrand);
    }
    
    //for (auto val : myvect) cout << val << " " ;
    //cout << myvect.size();

}


int main() {
    // just initialize random to something..
    srand(114552);

    // decide how many entries to generate
    int n = 100000;

    auto startTime = system_clock::now();
    do_container< vector<int> >(n);
    auto endTime = system_clock::now();
    auto ms = duration_cast<milliseconds>( endTime - startTime).count();
    cout << "do_container<vector>() inserting " << n << " times took "
         << ms << "ms\n";

    startTime = system_clock::now();
    do_container< list<int> >(n);
    endTime = system_clock::now();
    ms = duration_cast<milliseconds>( endTime - startTime).count();
    cout << "do_container<list>() inserting " << n << " times took "
         << ms << "ms" << endl;
}

