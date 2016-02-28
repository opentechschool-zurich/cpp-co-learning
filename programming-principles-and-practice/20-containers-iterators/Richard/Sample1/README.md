# Old Style iterating through a vector

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/20-containers-and-iterators/Richard/Sample1
mkdir build
cd build
cmake ..
make
./Sample1
```


``` cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> myIntVector {1,4,8};

    for( int i=0; i < myIntVector.size(); i++)
    {
        cout << myIntVector[i]<<" ";
        //Should output 1 4 8
    }
    return 0;
}
```

