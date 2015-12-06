#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void tolower(string& s) {
	for (char& x : s) x = tolower(x);
}


int main()
{


	string wort;

	ifstream buchOrginal{ "ReadMe.txt" };
	ofstream buchKopie{ "Kopie.txt" };

	if (buchOrginal.bad()) {
		cout << "error beim Einlesen" << endl;
	}
	if (buchKopie.bad()) {
		cout << "error beim Kopieren" << endl;
	}

	while (buchOrginal) {
		buchOrginal >> wort;
		tolower(wort);
		buchKopie << wort << " ";
}



	return 0;
}

