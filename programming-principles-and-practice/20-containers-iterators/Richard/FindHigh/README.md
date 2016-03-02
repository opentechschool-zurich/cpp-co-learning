# Iteration to find the highest value of a container

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/20-containers-and-iterators/Richard/FindHigh
mkdir build
cd build
cmake ..
make
./FindHigh
```


``` cpp
#include <vector>
#include <list>
#include <iostream>

using namespace std;

// return an iterator to the element in [first:last) that has the highest value
template<typename Iterator>
Iterator high(Iterator first, Iterator last) {
    Iterator high = first;
    for (Iterator it = first; it != last; ++it) {
        if (*high < *it) high = it;
    }
    return high;
}

int main() {
    vector <int> myIntVector {1, 4, 8};
    list <int> myIntList {10, 4, 8};
    cout << "High in myIntVector: " << *high(myIntVector.begin(), myIntVector.end()) << endl;
    cout << "High in myIntList: " << *high(myIntList.begin(), myIntList.end()) << endl;

    return 0;
}
```
