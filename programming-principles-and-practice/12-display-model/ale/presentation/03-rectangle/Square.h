#ifndef SQUARE_H
#define SQUARE_H
class Square
{
public:
    Square() {};
    void setWidth(const int w) {width = w;};
    int getArea() const;
    int virtual getGlitch() const {return 1;} 
protected:
    int width{0};
};
#endif
