#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

float BMI(int, int);
string BMIklasse(float);

int main()
{
	int Gewicht;
	int Groesse;
	cout << "Groesse in cm = ";
	cin >> Groesse;
	cout << "Gewicht in kg = ";
	cin >> Gewicht;

	float deinBMI = BMI(Gewicht, Groesse);
	string deinBMIklasse = BMIklasse(deinBMI);

	cout << "Dein BMI: " << deinBMI << '\n';
	cout << "Dein BMI ist ein Zeichen dass Du " << deinBMIklasse << " bist\n";

	return 0;
}

float BMI(int weight, int size)
{
	float sizeInMeters = ((float)size) / 100;
	return (float)weight / sizeInMeters / sizeInMeters;
}

string BMIklasse(float BMIvalue)
{
	if (BMIvalue < 18.5)
		return "untergewichtig";

	if (BMIvalue < 25.0)
		return "normalgewichtig";

	if (BMIvalue < 30.0)
		return "?bergewichtig";

	return "adipoes";
}
