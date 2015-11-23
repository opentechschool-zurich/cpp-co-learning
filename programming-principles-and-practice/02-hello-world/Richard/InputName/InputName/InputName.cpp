// InputName.cpp : read and write a first name.


#include "stdafx.h"

#include "std_lib_facilities.h"


int main()
{// C++ programs start by executing the function main
	
	cout << "Please enter your first name (followed by \"enter\"): "; 
	// output enter name
	string firstname;   //first name of string type
	cin >> firstname;    //read characters into first name object called firstname
	cout << "Hello, " << firstname << "!\n";
	return 0;
}
