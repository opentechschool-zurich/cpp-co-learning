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
