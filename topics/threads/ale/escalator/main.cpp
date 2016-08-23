#include<iostream>
#include<random>
#include<thread>
#include<mutex>
#include <condition_variable>

int direction = 0; // +1 up, -1 down, 0 stay

class Semaphore {
public:
    Semaphore (int count_ = 0)
        : count(count_) {}

    inline void notify()
    {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);

        while(count == 0){
            cv.wait(lock);
        }
        count--;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

std::mutex escalatorDirectionMutex;
Semaphore escalatorPeopleSemaphore(3);

void goUp()
{
    for (int i = 0; i < 10; i++) {

    }
}

void goDown()
{
}

int main()
{
    std::thread t1(goUp);
    std::thread t2(goDown);
    t1.join();
    t2.join();
}
