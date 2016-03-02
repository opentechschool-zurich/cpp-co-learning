# Iteration with auto

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/20-containers-and-iterators/Richard/Sample4
mkdir build
cd build
cmake ..
make
./Sample4
```


``` cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> myIntVector {1, 4, 8};
    //vector <int>::iterator myIntVectorIterator;

    for (auto myIntVectorIterator = myIntVector.begin();
            myIntVectorIterator != myIntVector.end();
            myIntVectorIterator++) {
        cout << *myIntVectorIterator << " ";
        //Should output 1 4 8
    }
    return 0;
}
```
