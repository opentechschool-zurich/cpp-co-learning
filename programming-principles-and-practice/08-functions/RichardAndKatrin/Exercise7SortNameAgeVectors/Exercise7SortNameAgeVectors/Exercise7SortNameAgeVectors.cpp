// Exercise7SortNameAgeVectors.cpp
// By Richard and Katrin 27 Oct 2015

#include "stdafx.h"  //required to compile on Windows with Visual Studio
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// copied from http://www.algolist.net/Algorithms/Sorting/Quicksort
// general info on sorting algos: http://www.sorting-algorithms.com/
void quickSort(vector<string>& names, vector<int>& ages, int left, int right) {
	int i = left, j = right;
	string tmpName;
	int tmpAge;
	string pivot = names[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (names[i] < pivot)
			i++;
		while (names[j] > pivot)
			j--;
		if (i <= j) {
			tmpName = names[i]; tmpAge = ages[i];
			names[i] = names[j]; ages[i] = ages[j];
			names[j] = tmpName; ages[j] = tmpAge;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(names, ages, left, j);
	if (i < right)
		quickSort(names, ages, i, right);
}

void sortVectors(vector<string>& names, vector<int>& ages) {
	quickSort(names, ages, 0, names.size()-1);
}



void printNameAgePairs( const vector<string>& names, const vector<int>& ages) {
	for (int i = 0; i < names.size(); ++i) {
		cout << names[i] << '\t' << ages[i] << '\n';
		//names[i] = "All your base are belong to us!"; //try to uncomment this (at your own peril...)
	}
}

int main()
{
	vector<string> names = { "John","Peter","John","Xavier","Anna" };
	vector<int> ages = { 15,22,31,22,5 };

	printNameAgePairs(names, ages);

	sortVectors(names, ages);

	cout << "Sorted by name:\n";
	printNameAgePairs(names, ages);

    return 0;
}

