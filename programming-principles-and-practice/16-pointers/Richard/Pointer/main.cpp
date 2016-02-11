#include <iostream>
#include <vector>

using namespace std;

void sizes() {
    cout << endl << "Memory sizes for various variable types on this computer:" << endl;
    cout << "The size of char is " << sizeof (char) << " bytes" <<  endl;
    cout << "The size of int is " << sizeof (int) << " bytes" << endl;
    cout << "The size of int* is " << sizeof (int*) << " bytes" << endl;
    cout << "The size of bool is " << sizeof (bool) << " bytes"  << endl;
    cout << "The size of double is " << sizeof (double) << " bytes"  << endl;
    cout << "The size of float is " << sizeof (float) << " bytes" << endl;
    vector<int> v(1000); // vector with 1000 elements of type int
    cout << "The size of vector<int>(1000) is " << sizeof (v)  << " bytes (which is a lie...)" << endl;
}

int main() {
    cout << "Creating a variable: int x = 17;" << endl;
    int x = 17;
    cout << "Creating a different variable: double e = 2.71828;" << endl;
    double e = 2.71828;

    cout << "Address of x: " << &x << " value of x: " << x << endl;
    cout << "Address of e: " << &e << " value of e: " << e << endl;

    double* addr_e = &e;
    int* addr_guess_x = ((int*) addr_e) + 3;
    cout << "Address guess for x which is 3 bytes(?) later: " << addr_guess_x << " value: " << *addr_guess_x << endl;

    sizes();

    return 0;
}

