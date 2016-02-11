# Pointers

This program experiments with creating variables and working with their address through a pointer.
It then takes the address of the second variable, adds 3 to it and ends up on the address of the first variable.
A subroutine prints out the memory sizes on the current computer.

```cpp
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
```

```bash
# to run:
mkdir build
cd build
cmake ..
make
./Pointer
```

It produces this output on a 64bit computer:

    Creating a variable: int x = 17;
    Creating a different variable: double e = 2.71828;
    Address of x: 0x7fffbca94d7c value of x: 17
    Address of e: 0x7fffbca94d70 value of e: 2.71828
    Address guess for x which is 3 bytes(?) later: 0x7fffbca94d7c value: 17

    Memory sizes for various variable types on this computer:
    The size of char is 1 bytes
    The size of int is 4 bytes
    The size of int* is 8 bytes
    The size of bool is 1 bytes
    The size of double is 8 bytes
    The size of float is 4 bytes
    The size of vector<int>(1000) is 24 bytes (which is a lie...)
