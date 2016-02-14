# Constructors

This program experiments with different kinds of constructors as per Bjarne's book Chapter 18.4 Essential Operations


Run it on-line with coliru:  <http://coliru.stacked-crooked.com/a/6c2e44d23f27a94a>


```cpp
#include <iostream>
#include <vector>

using namespace std;

struct X {
    int val;

    void out(const string& s, int nv) {
        cout << this << "–>" << s << ": " << val << " (" << nv << ")\n";
    }

    X() {
        out("X()", 0);
        val = 0;
    }// default constructor

    X(int v) {
        val = v;
        out("X(int)", v);
    }

    X(const X& x) {
        val = x.val;
        out("X(X&) ", x.val);
    }// copy constructor

    X& operator=(const X& a)// copy assignment
    {
        out("X::operator=()", a.val);
        val = a.val;
        return *this;
    }

    ~X() {
        out("~X()", 0);
    }// destructor
};


X glob(2); // a global variable

X copy(X a) {
    return a;
}

X copy2(X a) {
    X aa = a;
    return aa;
}

X& ref_to(X& a) {
    return a;
}

X* make(int i) {
    X a(i);
    return new X(a);
}

struct XX {
    X a;
    X b;
};

int main() {
    X loc{4}; // local variable
    X loc2{loc}; // copy construction
    loc = X{5}; // copy assignment
    loc2 = copy(loc); // call by value and return
    loc2 = copy2(loc);
    X loc3{6};
    X& r = ref_to(loc); // call by reference and return
    delete make(7);
    delete make(8);
    vector<X> v(4); // default values
    XX loc4;
    X* p = new X{9}; // an X on the free store
    delete p;
    X* pp = new X[5]; // an array of Xs on the free store
    delete[] pp;
}
```

```bash
# to run:
mkdir build
cd build
cmake ..
make
./Constructors
```

It produces this output on a 64bit computer:
```
0x6041f4–>X(int): 2 (2)
0x7ffdc725df40–>X(int): 4 (4)
0x7ffdc725df30–>X(X&) : 4 (4)
0x7ffdc725df50–>X(int): 5 (5)
0x7ffdc725df40–>X::operator=(): 4 (5)
0x7ffdc725df50–>~X(): 5 (0)
0x7ffdc725df70–>X(X&) : 5 (5)
0x7ffdc725df60–>X(X&) : 5 (5)
0x7ffdc725df30–>X::operator=(): 4 (5)
0x7ffdc725df60–>~X(): 5 (0)
0x7ffdc725df70–>~X(): 5 (0)
0x7ffdc725df90–>X(X&) : 5 (5)
0x7ffdc725df80–>X(X&) : 5 (5)
0x7ffdc725df30–>X::operator=(): 5 (5)
0x7ffdc725df80–>~X(): 5 (0)
0x7ffdc725df90–>~X(): 5 (0)
0x7ffdc725df20–>X(int): 6 (6)
0x7ffdc725dec0–>X(int): 7 (7)
0x24d3c50–>X(X&) : 7 (7)
0x7ffdc725dec0–>~X(): 7 (0)
0x24d3c50–>~X(): 7 (0)
0x7ffdc725dec0–>X(int): 8 (8)
0x24d3c50–>X(X&) : 8 (8)
0x7ffdc725dec0–>~X(): 8 (0)
0x24d3c50–>~X(): 8 (0)
0x24d3c50–>X(): 0 (0)
0x24d3c54–>X(): 0 (0)
0x24d3c58–>X(): 0 (0)
0x24d3c5c–>X(): 0 (0)
0x7ffdc725def0–>X(): 1818973744 (0)
0x7ffdc725def4–>X(): 32620 (0)
0x24d3c70–>X(int): 9 (9)
0x24d3c70–>~X(): 9 (0)
0x24d3c28–>X(): 4 (0)
0x24d3c2c–>X(): 0 (0)
0x24d3c30–>X(): -1 (0)
0x24d3c34–>X(): 0 (0)
0x24d3c38–>X(): 690509950 (0)
0x24d3c38–>~X(): 0 (0)
0x24d3c34–>~X(): 0 (0)
0x24d3c30–>~X(): 0 (0)
0x24d3c2c–>~X(): 0 (0)
0x24d3c28–>~X(): 0 (0)
0x7ffdc725def4–>~X(): 0 (0)
0x7ffdc725def0–>~X(): 0 (0)
0x24d3c50–>~X(): 0 (0)
0x24d3c54–>~X(): 0 (0)
0x24d3c58–>~X(): 0 (0)
0x24d3c5c–>~X(): 0 (0)
0x7ffdc725df20–>~X(): 6 (0)
0x7ffdc725df30–>~X(): 5 (0)
0x7ffdc725df40–>~X(): 5 (0)
0x6041f4–>~X(): 2 (0)
```