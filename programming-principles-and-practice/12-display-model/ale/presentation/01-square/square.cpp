#include <iostream>

using namespace std;

class Square
{
public:
    Square() {};
    void setWidth(const int w) {width = w;};
    int getArea() const;
private:
    int width{0};
};

int Square::getArea() const
{
    return width * width;
}

int main()
{
    Square square{};
    square.setWidth(10);
    cout << "Area: " << square.getArea() << endl;
    return 0;
}
