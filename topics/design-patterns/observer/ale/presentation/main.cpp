#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Subject
{
    public:
        void add(function<void(int)> f)
        {
            views.push_back(f);
        }
        void set(int v) {value = v; notify();}
    private:
        int value{0};
        vector<function<void(int)>> views;
        void notify()
        {
            for (auto f: views)
            {
                f(value);
            }
        }

};

class FirstView
{
    public:
        FirstView(Subject &mode)
        {
            auto lambda = [this](int value) {update(value);};
            mode.add(lambda);
        }
    private:
        void update(int value)
        {
            cout << "value: " << value << endl;
        }
    
};

int main()
{
    Subject subject;
    FirstView view1(subject);
    subject.set(15);
}
