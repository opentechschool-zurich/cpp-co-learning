// Bleep.cpp : Enter name and age without duplicates and print table.
// Chapter 4 Exercise 19

/* 19. Write a program where you first enter a set of name - and-value pairs,
such as Joe 17 and Barbara 22. For each pair, add the name to a vector 
called names and the number to a vector called scores (in corresponding 
positions, so that if names[7] == "Joe" then scores[7] == 17). Terminate
input with NoName 0. Check that each name is unique and terminate with an 
error message if a name is entered twice.Write out all the(name, score) 
pairs, one per line. */

#include "stdafx.h"
#include "std_lib_facilities.h"

int main() {
	cout << "Enter a name and the age. End with Ctrl-Z (If you enter the same name twice pgm ends): " << endl;

	string name; int age;
	vector <string> names;	vector <int> ages;

	cout << "enter name and age - end by entering no more \n";
	while (cin >> name >> age) {
		if (std::find(names.begin(), names.end(), name) != names.end()) {
			cout << "double entry \n";
			break;
		}
		else {
			names.push_back(name);
			ages.push_back(age);
		}
	}
	for (size_t i = 0; i < names.size(); i++) {
		cout << names[i] << "\t" << ages[i] << "\n";
	}
	return 0;
}

