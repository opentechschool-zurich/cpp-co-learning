// Chapter5Q7 quad equation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "std_lib_facilities.h"

class ImaginaryNumberException {};
class DivisionByZeroException {};

double getRootArgument(int A, int B, int C) {
	double rootArgument = B*B - 4 * A*C;
	if (rootArgument < 0.0) {
		throw ImaginaryNumberException();
	}
	if (A == 0) {
		throw DivisionByZeroException();
	}
	return rootArgument;
}


int main()
{
	//int a = 0; int b = 3; int c = 4;  // input a, b and c
	int a = 7; int b = 3; int c = 0;  // input a, b and c

	try {
		double delta = sqrt(getRootArgument(a, b, c));
		vector <double> quad_equation;
		quad_equation.push_back((-b + delta) / 2 / a);  // create function to calculate x1
		quad_equation.push_back((-b - delta) / 2 / a);  // create function to calculate x2
		cout << "x1 = " << quad_equation[0] << ", x2 = " << quad_equation[1] << '\n'; //print out the roots of of a quad equation
	}
	catch (ImaginaryNumberException) {
		cout << "No result for sqrt function!\n"; // with no real roots, have it print out a message
		return 1;
	}
	catch (DivisionByZeroException) {
		cout << "Division by Zero is not allowed!\n";
		return 1;
	}


	//keep_window_open();
	return 0;
}



