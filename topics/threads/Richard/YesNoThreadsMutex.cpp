#include <thread>
#include <mutex>
#include <iostream>
#include <random>
#include <chrono>

namespace {

std::mutex outputMutex;

class Guard {
public:
    explicit Guard(std::mutex& m): m{m} {m.lock();}
    ~Guard() {m.unlock();}
private:
    std::mutex& m;
};

void sleepRandomTime() {
    std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
    std::uniform_int_distribution<> dist{5, 80};
    std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
}

void YesFunction() {
    try {
    for ( int i = 1; i < 10; ++i ) {
        // the mutex is locked when the guard is created and is unlocked when it goes out of scope
        {
            Guard g(outputMutex);
            std::cout << "Yes (" << i << ')'<< std::endl;
            if (i == 5) {
                throw 5;
            }
        }
        sleepRandomTime();
    }
    } catch (...) {
    }

}

void NoFunction() {
    for ( int i = 1; i < 10; ++i ) {
        outputMutex.lock();
        std::cout << "No (" << i << ')'<< std::endl;
        outputMutex.unlock();
        sleepRandomTime();
    }
}

}

int main() {
    std::thread t1(YesFunction);
    std::thread t2(NoFunction);
    t1.join();
    t2.join();
}
