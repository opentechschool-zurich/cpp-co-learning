// Chapter4Q20.cpp : Enter name and age without duplicates and print age of entered name.
//
#include "stdafx.h"
#include "std_lib_facilities.h"


char answer = ask_user("Do you want ice cream");

int main() {
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
	cout << "enter name to search for: \n";
	string search_name;
	cin >> search_name;
	for (size_t i = 0; i < names.size(); i++) {
		if (search_name == names[i]) {
			cout << ages[i] << "\n";
		}
		
	}
	return 0;
}




