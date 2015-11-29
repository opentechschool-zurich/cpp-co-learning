#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
int main()
{
	ifstream inputStream { "integers.dta" };
	int integerValue = 0; int sum = 0;
	while (inputStream >> integerValue) {
		sum += integerValue;
		//cout << sum << endl;
	}

	if (inputStream.eof()) {
		//cout << "inputStream is eof this is OK\n";
		cout << "sum: " << sum << endl;
	}
	if (inputStream.bad()) {
		//cout << "inputStream is bad --> we should throw away the data and throw an exception!\n";
		cout << "No result, bad input" << endl;
	}
	if (inputStream.fail() && ! inputStream.eof()) {
		//cout << "inputStream is fail--> we should throw away the data and throw an exception!\n";
		cout << "No result, bad input" << endl;
	}
	if (inputStream.good()) {
		cout << "inputStream is good that is a bit unexpected....\n";
	}

	return 0;
}

