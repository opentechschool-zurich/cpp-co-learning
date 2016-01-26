class Square
{
public:
    Square() {};
    void setWidth(const int w) {width = w;};
    int getArea() const;
protected:
    int width{0};
};
