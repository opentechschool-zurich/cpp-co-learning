#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

void do_something() {
    vector<int> pointless {0,1,2,3,4,5};
}

// repeat do_something() n times
int main() {
    int n = 10000000;
    auto startTime = system_clock::now();
    for (int i = 0; i<n; i++) // timing loop
        do_something();
    auto endTime = system_clock::now();
    auto ms = duration_cast<milliseconds>( endTime - startTime).count();
    cout << "do_something() " << n << " times took "
        << ms << "ms\n";
}
