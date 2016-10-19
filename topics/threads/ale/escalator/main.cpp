#include<iostream>
#include <algorithm>
#include<vector>
#include<random>
#include<thread>
#include<mutex>
#include <condition_variable>


/**
 * - producer up
 * - producer down
 * - two queues
 * - a consumer (the escalator that can go up and down)
 */

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

// TODO: use std::unique_lock<std::mutex> instead
class Guard {
public:
    explicit Guard(std::mutex& m): m{m} {m.lock();}
    ~Guard() {m.unlock();}
private:
    std::mutex& m;
};

/**
 * return a random delay between 1000 and 5000 milliseconds
 */
int getRandomDelay()
{
    static std::mt19937_64 eng{std::random_device{}()};
    static std::uniform_int_distribution<> dist{1000, 5000};
    return dist(eng);
}

int waitingUpwards = 0;
int waitingDownwards = 0;
std::mutex waitingUpwardsMutex;
std::mutex waitingDownwardsMutex;
std::mutex outputMutex;

std::vector<int>going;

int stepsToGo = 0;
int direction = 0; // +1 up, -1 down, 0 stay

void goUp()
{
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds{getRandomDelay()});
        {
            Guard g(outputMutex);
            std::cout << "up " << i << std::endl;
        }
        Guard g(waitingUpwardsMutex);
        waitingUpwards++;
    }
}

void goDown()
{
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds{getRandomDelay()});
        {
            Guard g(outputMutex);
            std::cout << "down " << i << std::endl;
        }
        Guard g(waitingDownwardsMutex);
        waitingDownwards++;
    }
}

void printStatus()
{
    Guard g(outputMutex);
    std::cout << std::endl;
    if (direction == 0) {
        std::cout << "stopped" << std::endl;
    } else {
        std::cout << "going " << (direction == 1 ? "up" : "down") << std::endl;
        std::cout << waitingUpwards << " waiting upwards" << std::endl;
        std::cout << waitingDownwards << " waiting downwwards" << std::endl;
        std::cout << (going.empty() ? 0 : going.back()) << " steps to do before stopping" << std::endl;
    }
}

/**
 * once a second, move by one step
 */
void runEscalator()
{
    // TODO: use the mutexes (also for std::cout
    // TODO: max n people on the escalator
    while (true) {
        if (direction == 0) {
            if (waitingUpwards > 0) {
                direction = 1;
            } else if (waitingDownwards > 0) {
                direction = -1;
            }
        } else {
            for (auto && steps: going) {
                steps--;
            }


            if (!going.empty()) {
                int first = going.front();
                if (first == 0) {
                    going.erase(going.begin());
                }
            }

            if (going.empty()) {
                direction = 0;
            }
        }

        if (direction == 1) {
            Guard g(waitingUpwardsMutex);
            if (waitingUpwards > 0) {
                waitingUpwards--;
                going.push_back(5);
            }
        } else if (direction == -1) {
            Guard g(waitingDownwardsMutex);
            if (waitingDownwards > 0) {
                waitingDownwards--;
                going.push_back(5);
            }
        }
        printStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}

int main()
{
    std::thread goingUp(goUp);
    std::thread goingDown(goDown);
    std::thread runningEscalator(runEscalator);
    goingUp.join();
    goingDown.join();
    runningEscalator.join();
}
