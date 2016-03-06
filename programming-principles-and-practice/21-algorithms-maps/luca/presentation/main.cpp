
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

bool isBiggerThan_2 (int i) {
  return i > 2;
}


class myDynamicBiggerThan {
private:
    int thanThis;

public:
    myDynamicBiggerThan(int biggerThan)
        : thanThis(biggerThan) {}

    bool operator ()(int i) {
        return i > thanThis;
    }
};


int main () {

    vector<int> myvector {1, 2, 3, 4};

    // with global function
    auto it = find_if (myvector.begin(), myvector.end(), isBiggerThan_2);
    if ( it != myvector.end() ) {
        cout << "first result with global function isBiggerThan_2         is: " << *it << endl;
    }

    // with function object
    it = find_if (myvector.begin(), myvector.end(), myDynamicBiggerThan(3));
    if ( it != myvector.end() ) {
        cout << "first result with function object myDynamicBiggerThan(3) is: " << *it << endl;
    }


}
