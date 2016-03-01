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
    
    int myrand = rand() % n;
    myvect.push_back(myrand);
    
    for (int i = 0; i<n; i++) { // timing loop
      myrand = rand() % n;
      
      // loop all the vector looking for the element to insert before it
      auto it = myvect.begin();
      for ( ;it!=myvect.end(); ++it) {
	if (*it > myrand) {
	  // once found insert and exit the loop
	  myvect.insert(it, myrand);
	  break;
	}
      }
      // if we are here and iterator is at the end
      // it means we did not insert anything yet, so push at the end
      if ( it == myvect.end() )
	myvect.push_back(myrand);
      
      
    }
    
//    for (auto val : myvect) cout << val << " " ;
  
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

