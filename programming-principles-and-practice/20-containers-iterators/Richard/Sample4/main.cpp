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
