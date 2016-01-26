class Square
{
public:
    Square() {};
    void setWidth(const int w) {width = w;};
    int getArea() const;
private:
    int width{0};
};
