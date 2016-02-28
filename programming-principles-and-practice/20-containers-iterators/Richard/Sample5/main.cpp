#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> myIntVector {1, 4, 8};

    for (auto element : myIntVector) {
        cout << element << " ";
        //Should output 1 4 8
    }
    return 0;
}
