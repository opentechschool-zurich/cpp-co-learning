# Reverse Iteration

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/20-containers-and-iterators/Richard/Sample3
mkdir build
cd build
cmake ..
make
./Sample3
```


``` cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> myIntVector {1, 4, 8};
    vector <int>::reverse_iterator myIntVectorIterator;

    for (myIntVectorIterator = myIntVector.rbegin();
            myIntVectorIterator != myIntVector.rend();
            myIntVectorIterator++) {
        cout << *myIntVectorIterator << " ";
        //Should output 8 4 1
    }
    return 0;
}
```
