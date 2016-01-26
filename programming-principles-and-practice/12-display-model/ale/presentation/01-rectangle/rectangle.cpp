#include <iostream>

using namespace std;

class Rectangle
{
public:
    Rectangle() {};
    void setWidth(int w) {width = w;};
    void setHeight(int h) {height = h;};
    int getArea();
private:
    int width{0};
    int height{0};
};

int Rectangle::getArea()
{
    return height * width;
}

int main()
{
    Rectangle rectangle{};
    rectangle.setWidth(10);
    rectangle.setHeight(5);
    cout << "Area: " << rectangle.getArea() << endl;
    return 0;
}
