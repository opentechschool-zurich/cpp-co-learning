#include <thread>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void sleepRandomTime() {
    std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
    std::uniform_int_distribution<> dist{5, 80};
    std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
}

void YesFunction() {
    for ( int i = 1; i < 10; ++i ) {
        std::cout << "Yes (" << i << ')'<< std::endl;
        sleepRandomTime();
    }
}

void NoFunction() {
    for ( int i = 1; i < 10; ++i ) {
        std::cout << "No (" << i << ')'<< std::endl;
        sleepRandomTime();
    }
}

int main() {
    std::thread t1(YesFunction);
    std::thread t2(NoFunction);
    t1.join();
    t2.join();
}
