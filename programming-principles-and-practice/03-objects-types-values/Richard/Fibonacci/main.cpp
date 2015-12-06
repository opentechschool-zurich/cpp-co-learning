/* 
 * File:   main.cpp
 * Author: Richard Eigenmann
 *
 * Created on September 29, 2015, 9:21 PM
 */

#include <cstdlib>
#include "std_lib_facilities.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Fibonacci Numbers:\n";
    int prior = 1;
    cout << prior << " ";

    int current = 1;

    for (int i = 0; i < 100; i++) {
        cout << current << " ";
        int next = prior + current;
        if ( next < 0 ) {
            cout << "\nUnsafe addition at i=" << i <"\n";
            break;
        }
        prior = current;
        current = next;
    }
    return 0;
}

