#include <iostream>
#include<string>
#include<vector>

using namespace std;

class X {
public:
    int val;
    void out(const string& s, int nv)
        {cerr << this << "->" << s << ":" << val << "(" << nv << ")" << endl;}
    X()
        {out("X()", 0); val = 0;};
    X(int v)
        {val = v; out("X(int)", v);};
    X(const X& x)
        {val = x.val; out("X(X&)", x.val);};
    X& operator=(const X& a)
        {out("X& X(X&)", a.val); val = a.val; return *this;};
    ~X()
        {out("~X()", val);};
};

X glob(2);

X copy(X a) {return a;}
X copy2(X a) {X aa = a; return aa;}
X&ref_to(X& a) {return a;}
X* make(int i) {X a(i); return new X(a);}

struct XX {X a; X b;};

int main()
{
    cout << "main()" << endl;
    X loc{4};
    cout << "..." << endl;
    X loc2{loc};
    cout << "..." << endl;
    loc = X{5};
    cout << "..." << endl;
    loc2 = copy(loc);
    cout << "..." << endl;
    loc2 = copy2(loc);
    cout << "..." << endl;
    X loc3{6};
    cout << "..." << endl;
    X&r = ref_to(loc);
    cout << "..." << endl;
    delete make(7);
    cout << "..." << endl;
    delete make(8);
    cout << "..." << endl;
    vector<X> v(4);
    cout << "..." << endl;
    XX loc4;
    cout << "..." << endl;
    X* p = new X{9};
    cout << "..." << endl;
    delete p;
    cout << "..." << endl;
    X* pp = new X[5];
    cout << "..." << endl;
    delete[] pp;
}
