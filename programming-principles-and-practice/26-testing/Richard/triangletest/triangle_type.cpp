#include "triangle_type.h"

#include <string>

using namespace std;

string triangle_type(int a, int b, int c) {
	if (a < 0 || b < 0 || c < 0) {
		return "Negative Number not allowed!";
	}

	if (a + b <=  c || a + c <= b || b + c <= a ) {
		return "Not a triangle";
	}

	if (a == b && b == c) {
		return "Equilateral";
	}

	if (a == b || b == c || a == c) {
		return "Isosceles";
	}

	return "Scalene";
	
}