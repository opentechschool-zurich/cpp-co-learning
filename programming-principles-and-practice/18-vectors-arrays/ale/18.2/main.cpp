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
    ~Vector()
        {delete[] elem;}
};

int main() {
    Vector v1(2);
    Vector v2 = {1.2, 7.89, 12.34};
    
    return 0;
}
