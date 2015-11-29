// Chapter4Q1.cpp 
//

#include "stdafx.h"
#include "std_lib_facilities.h"


int main()
{
	double amount = 1;
	char currency = 0;
	while (amount > 0) {
		cout << "enter value and first letter of currency \n";
		cin >> amount >> currency;
		constexpr double chf_to_usd = 1.03;
		constexpr double eur_to_usd = 1.13;
		constexpr double pound_to_usd = 1.55;
		constexpr double yuan_to_usd = 0.156;

		switch (currency) {
		case 'c':
			cout << amount << " chf are " << chf_to_usd * amount << " USD \n";
			break;
		case 'e':
			cout << amount << " euro are " << eur_to_usd * amount << " USD \n";
			break;
		case 'p':
			cout << amount << " pound are " << pound_to_usd * amount << " USD \n";
			break;
		case 'y':
			cout << amount << " yuan are " << yuan_to_usd * amount << " USD \n";
			break;

		default:
			cout << "no valid entry \n";
			break;

		}
	}

	return 0;
}
