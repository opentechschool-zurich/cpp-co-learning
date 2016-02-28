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
        //Should output 1 4 8
    }
    return 0;
}
