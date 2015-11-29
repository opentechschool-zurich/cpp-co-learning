// Chapter4Q19.cpp : Enter name and age without duplicates and print table.
//
#include "stdafx.h"
#include <std_lib_facilities.h>

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
	for (size_t i = 0; i < names.size(); i++) {
		cout << names[i] << "\t" << ages[i] << "\n";
	}
	return 0;
}

int main()
{
    return 0;
}

