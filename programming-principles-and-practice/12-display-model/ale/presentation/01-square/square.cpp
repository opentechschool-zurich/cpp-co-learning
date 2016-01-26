#include <iostream>

using namespace std;

class Square
{
public:
    Square() {};
    void setWidth(const int w) {width = w;};
    void setHeight(const int h) {height = h;};
    int getArea() const;
private:
    int width{0};
    int height{0};
};

int Square::getArea() const
{
    return height * width;
}

int main()
{
    Square square{};
    square.setWidth(10);
    square.setHeight(5);
    cout << "Area: " << square.getArea() << endl;
    return 0;
}
