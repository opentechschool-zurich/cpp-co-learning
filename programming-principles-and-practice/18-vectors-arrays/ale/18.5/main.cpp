#include<iostream>
#include<initializer_list>
#include<iterator> // for std::copy

using namespace std;

class Vector {
private:
    long unsigned int sz;
    double* elem;
public:
    Vector(long unsigned int s)
    :sz{s}, elem{new double[s]}
    {
        for (int i = 0; i < sz; i++) {elem[i] = 0.0;}
    };
    Vector(initializer_list<double> lst)
    :sz{lst.size()}, elem{new double[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    };
    Vector(const Vector&); // copy constructor
    Vector& operator=(const Vector&); // copy assignment
    Vector(Vector&&); // move constructor
    Vector& operator=(Vector&&); // move assignment

    void set(int pos, double val) {elem[pos] = val;}
    double get(int pos) {return elem[pos];}
    double& operator[](int n) {return elem[n];};
    double operator[](int n) const {return elem[n];};
    ~Vector()
        {delete[] elem;}
};

Vector::Vector(const Vector& v)
    :sz{v.sz}, elem{new double[v.sz]}
{
    copy(v.elem, v.elem + sz, elem);
}

Vector& Vector::operator=(const Vector& v)
{
    double* p = new double[v.sz];
    copy(v.elem, v.elem + v.sz, p);
    delete[] elem;
    elem = p;
    sz = v.sz;
    return *this;
}

Vector::Vector(Vector&& v)
    :sz{v.sz}, elem{v.elem}
{
    v.sz = 0;
    v.elem = nullptr;
}

Vector& Vector::operator=(Vector&& v)
{
    delete[] elem;
    elem = v.elem;
    sz = v.sz;
    v.elem = nullptr;
    v.sz = 0;
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

    cout << "v3[2]: " << v3[2] << endl;

    v3[2] = 5.0;
    cout << "v3[2]: " << v3[2] << endl;

    return 0;
}
