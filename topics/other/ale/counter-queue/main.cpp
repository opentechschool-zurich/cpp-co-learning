#include <iostream>
#include <queue>

// TODO: make the queue const (its content won't be const)

class A
{
    int counter = 0;
    int increment = 1;
    std::queue<std::string>& queue;
    public:
    A(std::queue<std::string>& q): queue{q} {};
    void count() {
        if (queue.front() == "a double") {
            increment = 2;
            queue.pop();
        }
        counter += increment;
        std::cout << "a / " << counter << std::endl;
        if (counter == 10) {
            queue.push("b start");
        }
    }
};

class B
{
    int counter = 0;
    std::queue<std::string>& queue;
    bool active = false;
    public:
    B(std::queue<std::string>& q): queue{q} {};
    void count() {
        if (!active && queue.front() == "b start") {
            active = true;
            queue.pop();
        }
        if (active) {
            counter++;
            std::cout << "b / " << counter << std::endl;
            if (counter == 10) {
                queue.push("a double");
                active = false;
            }
        }
    }
};

int main()
{
    std::queue<std::string> q;
    A a(q);
    B b(q);
    for (int i = 0; i < 30; i++) {
        a.count();
        b.count();
    }
}
