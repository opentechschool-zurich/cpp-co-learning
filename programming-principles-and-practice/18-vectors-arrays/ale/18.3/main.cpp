#include<iostream>
#include<initializer_list>
#include<iterator> // for std::copy

using namespace std;

class Vector {
private:
    long unsigned int size;
    double* elem;
public:
    Vector(long unsigned int s)
    :size{s}, elem{new double[s]}
    {
        for (int i = 0; i < size; i++) {elem[i] = 0.0;}
    };
    Vector(initializer_list<double> lst)
    :size{lst.size()}, elem{new double[size]}
    {
        copy(lst.begin(), lst.end(), elem);
    };
    Vector(const Vector&); // copy constructor
    Vector& operator=(const Vector&); // copy assignment
    Vector(Vector&&); // move constructor
    Vector& operator=(Vector&&); // move assignment

    void set(int pos, double val) {elem[pos] = val;}
    double get(int pos) {return elem[pos];}
    ~Vector()
        {delete[] elem;}
};

Vector::Vector(const Vector& v)
    :size{v.size}, elem{new double[v.size]}
{
    copy(v.elem, v.elem + size, elem);
}

Vector& Vector::operator=(const Vector& v)
{
    double* p = new double[v.size];
    copy(v.elem, v.elem + v.size, p);
    delete[] elem;
    elem = p;
    size = v.size;
    return *this;
}

Vector::Vector(Vector&& v)
    :size{v.size}, elem{v.elem}
{
    v.size = 0;
    v.elem = nullptr;
}

Vector& Vector::operator=(Vector&& v)
{
    delete[] elem;
    elem = v.elem;
    size = v.size;
    v.elem = nullptr;
    v.size = 0;
    return *this;
}

int main() {
    Vector v1(3);
    v1.set(2, 2.22);
    Vector v2 = v1;

    Vector v3(4);
    v3 = v1;
    cout << "v1[2]: " << v1.get(2) << endl;
    cout << "v1[2]: " << v2.get(2) << endl;
    cout << "v3[2]: " << v3.get(2) << endl;

    return 0;
}
