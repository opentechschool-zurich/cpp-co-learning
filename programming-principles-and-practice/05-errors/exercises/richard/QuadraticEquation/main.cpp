/* 
 * File:   main.cpp
 * Author: Richard Eigenmann
 *
 * Created on September 29, 2015, 8:03 PM
 */

#include <cstdlib>
#include "std_lib_facilities.h"

class ImaginaryNumberException {
};

/**
 * Returns a vector with the two double results for the quadratic equation
 * or throws a ImaginaryNumberException
 */
vector<double> quad_results(double a, double b, double c) {
    double rootArgument = pow(b, 2) - 4 * a * c;
    if (rootArgument < 0) {
        throw ImaginaryNumberException();
    }
    vector<double> resultVector;
    resultVector.push_back( ( (-1.0) * b + sqrt(rootArgument)) / 2 / a );
    resultVector.push_back( ( (-1.0) * b - sqrt(rootArgument)) / 2 / a );
    return resultVector;
}


void print_quad_equation(double a, double b, double c) {
    cout << "Equation: " << a << "*x^2 + " << b << "*x + " << c << " = 0\n";
    try {
        vector<double> results = quad_results(a, b, c);
        double x1 = results[0];
        cout << "      x1: " << x1 << "\n";
        cout << "          " << a * x1 * x1 << " + " << b * x1 << " + " << c << " = " << a * x1 * x1 + b * x1 + c << '\n';
        double x2 = results[1];
        cout << "      x2: " << x2 << "\n";
        cout << "          " << a * x2 * x2 << " + " << b * x2 << " + " << c << " = " << a * x2 * x2 + b * x2 + c << "\n\n";
    } catch (ImaginaryNumberException) {
        cout << "No real results\n\n";
    }
}

int main(int argc, char** argv) {
    cout << "Sample Quadratic Equations:\n";
    print_quad_equation(7.0, 3.0, 0.0);
    print_quad_equation(2.0, 5.0, 3.0);
    print_quad_equation(4.0, 5.0, 3.0);
    return 0;
}

