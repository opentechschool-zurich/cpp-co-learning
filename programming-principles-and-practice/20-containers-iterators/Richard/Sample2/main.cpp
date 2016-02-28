#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> myIntVector {1, 4, 8};
    vector <int>::iterator myIntVectorIterator;

    for (myIntVectorIterator = myIntVector.begin();
            myIntVectorIterator != myIntVector.end();
            myIntVectorIterator++) {
        cout << *myIntVectorIterator << " ";
        //Should output 8 4 1
    }
    return 0;
}
