// vendingmachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int drink=0;

	cout << "Choose your drink: Press 1 for Cola, 2 for water and 3 for lemonade\n";
	cin >> drink;

	if (drink == 1)
		cout << "You pressed "<< drink<< " so you chose Cola\n";
	if (drink == 2)
		cout << "You pressed " << drink << " so you chose Water\n";
	if (drink == 3)
		cout << "You pressed " << drink << " so you chose Lemonade\n";

	return 0;
}

