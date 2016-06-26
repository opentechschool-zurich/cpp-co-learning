#include "stdafx.h"
#include <iostream>
using namespace std;

// create a class Fizz that can hold a value 
// it has a member function to print the value
class Fizz {
private:
	int value;
public:
	Fizz(int val);  // says there will be a constructor
	void printValue() { cout << "Fizz (" << value << ")" << endl; };
};
Fizz::Fizz(int val) : value(val) {} //defines how the constuctor works

class Buzz {
private:
	int value;
public:
	Buzz(int val);
	void printValue() { cout << "Buzz (" << value << ")" << endl; };
};
Buzz::Buzz(int val) : value(val) {}

class FizzBuzz {
private:
	int value;
public:
	FizzBuzz(int val);
	void printValue() { cout << "FizzBuzz (" << value << ")" << endl; };
};
FizzBuzz::FizzBuzz(int val) : value(val) {}

int main() {
	for (int i = 1; i <= 30; i++) {
		try {
			if (i % 3 == 0 && i % 5 == 0)
				throw  FizzBuzz(i);
			else
				if (i % 3 == 0)
					throw Fizz(i);
				else
					if (i % 5 == 0)
						throw Buzz(i);
					else cout << i << endl;
		} catch (FizzBuzz fb) {
			fb.printValue(); cout << "FizzBuzz" << endl;
		} catch (Buzz b) {
			b.printValue();
		} catch (Fizz f) {
			f.printValue();
		}
	}
	return 0;
}
