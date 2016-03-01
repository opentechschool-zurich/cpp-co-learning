#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>

using namespace std;
using namespace chrono;

void doPushBack(int n) {
    vector<int> v;

    auto startTime = system_clock::now();
    for (int i = 0; i<n; i++) {
        int r = rand() % n;
        v.push_back(r);
        cout << "\r" << i;
    }
    auto endTime = system_clock::now();

    auto ms = duration_cast<milliseconds>( endTime - startTime).count();

    cout << "vector push_back" << n << " times took " << ms << "ms\n";
}

void doVectorSort(int n) {
    vector<int> v;

    auto startTime = system_clock::now();
    for (int i = 0; i<n; i++) {
        int r = rand() % n;
        v.push_back(r);
        cout << "\r" << i;
    }
    sort(v.begin(), v.end());

    auto endTime = system_clock::now();

    auto ms = duration_cast<milliseconds>( endTime - startTime).count();

    cout << "vector sort" << n << " times took " << ms << "ms\n";
}

void doList(int n) {
    list<int> l;

    auto startTime = system_clock::now();
    for (int i = 0; i<n; i++) {
        int r = rand() % n;
        auto el = l.end();
        for (auto it = l.begin(); it != l.end(); it++) {
            el = it;
            if (*it > r) {
                break;
            }
        }
        l.insert(el, r);
        cout << "\r" << i;
    }
    auto endTime = system_clock::now();

    auto ms = duration_cast<milliseconds>( endTime - startTime).count();

    cout << "list " << n << " times took " << ms << "ms\n";
}

void doVector(int n) {
    vector<int> v;

    auto startTime = system_clock::now();
    for (int i = 0; i<n; i++) {
        int r = rand() % n;
        auto el = v.end();
        for (auto it = v.begin(); it != v.end(); it++) {
            el = it;
            if (*it > r) {
                break;
            }
        }
        v.insert(el, r);
        cout << "\r" << i;
    }
    auto endTime = system_clock::now();

    auto ms = duration_cast<milliseconds>( endTime - startTime).count();

    cout << "vector " << n << " times took " << ms << "ms\n";
}


// repeat do_something() n times
int main() {

    srand (time(NULL));

    // int n = 10000000;
    // int n = 1000000;

    int n = 10000;
    // list 10000 times took 594ms
    // vector 10000 times took 867ms

    // int n = 100000;
    // list 100000 times took 94737ms
    // vector 100000 times took 86841ms
    // list 100000 times took 92470ms
    // vector 100000 times took 86814ms

    doList(n);
    doVector(n);
    doPushBack(n);
    doVectorSort(n);

}
