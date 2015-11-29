// type names and scores in a table without repeated names

#include "stdafx.h"
#include "std_lib_facilities.h"


bool isRepeated(string name, vector <string> names) {
	for (string name_from_vector : names) {
		if (name == name_from_vector) {
			return true;
		}
	}
	return false;
}

int main() {
	vector<string> names;
	vector<int> scores;

	while (true) {
		cout << "Please type a name with a score:\n";
		string name;
		int score;
		cin >> name >> score;

		if (isRepeated(name, names)) {
			cout << "Repetition!\n";
			break;
		}

		names.push_back(name);
		scores.push_back(score);
	}
	cout << "Names and scores:\n";
	for (size_t i = 0; i < names.size(); ++i)
		cout << names[i] << "\t" << scores[i] << "\n";

	return 0;
}

