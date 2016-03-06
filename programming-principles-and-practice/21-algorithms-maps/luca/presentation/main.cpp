
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int x;
bool isBiggerThan_x (int i) {
  return i > x;
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
    x = 2;
    auto it = find_if (myvector.begin(), myvector.end(), isBiggerThan_x);
    if ( it != myvector.end() ) {
        cout << "first result with global function isBiggerThan_x x=2     is: " << *it << endl;
    }

    // with function object
    it = find_if (myvector.begin(), myvector.end(), myDynamicBiggerThan(3));
    if ( it != myvector.end() ) {
        cout << "first result with function object myDynamicBiggerThan(3) is: " << *it << endl;
    }

    // with lambda function
    int bigger = 1;
    it = find_if (myvector.begin(), myvector.end(), [=](int i){ return i > bigger; });
    if ( it != myvector.end() ) {
        cout << "first result with lambda function using the var bigger=1 is: " << *it << endl;
    }
}
