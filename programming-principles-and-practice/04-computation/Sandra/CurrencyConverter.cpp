// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
	int currency1 = 0, value = 0, currency2 = 0;
	double rate = 0;

	cout << "Currency Converter Using Switch.   *Market values accurate as of 07/06/2016*\n" << endl;

	do
	{
		cout << "Available Currencies:\n---------------------\n| (1) Euro          |\n"
			<< "| (2) SFr           |\n| (3) Dollar        |\n| (4) Yen           |\n| (5) Danish Krone  |"
			<< "\n| (6) Chinese Yuan  |\n---------------------\n\n";

		cout << "Currencies are chosen by entering their corresponding index value.\n\n";
		cout << "Please choose a currency: ";
		cin >> currency1;

		switch (currency1)
		{
		case 1:
			cout << "\nYou have selected Euro.\n\n"
				<< "Please choose a value in Euro: ";
			cin >> value;
			cout << "\nYou have chosen " << value << " Euro.\n\n"
				<< "Please choose the currency you wish to convert to: ";
			cin >> currency2;

			switch (currency2)
			{
			case 1:
				cout << "\nYou have chosen Euro.\n\n";
				rate = value * 1;
				cout << value << " Euro == " << rate << " Euro.\n\n\n\n";
				break;
			case 2:
				cout << "\nYou have chosen SFr.\n\n";
				rate = value * 0.9677;
				cout << value << " Euro == " << rate << " SFr.\n\n\n\n";
				break;
			case 3:
				cout << "\nYou have chosen Dollars.\n\n";
				rate = value * 0.8815;
				cout << value << " Euro == " << rate << " Dollars.\n\n\n\n";
				break;
			case 4:
				cout << "\nYou have chosen Yen.\n\n";
				rate = value * 111.870;
				cout << value << " Euro == " << rate << " Yen.\n\n\n\n";
				break;
			case 5:
				cout << "\nYou have chosen Danish Krone.\n\n";
				rate = value * 7.45595;
				cout << value << " Euro == " << rate << " Danish Krone.\n\n\n\n";
				break;
			case 6:
				cout << "\nYou have chosen Chinese Yuan.\n\n";
				rate = value * 8.27564;
				cout << value << " Euro == " << rate << " Chinese Yuan.\n\n\n\n";
				break;
			}

		case 2:
			cout << "\nYou have selected Sfr.\n\n"
				<< "Please choose a value in SFr: ";
			cin >> value;
			cout << "\nYou have chosen " << value << " SFr.\n\n"
				<< "Please choose the currency you wish to convert to: ";
			cin >> currency2;

			switch (currency2)
			{
			case 1:
				cout << "\nYou have chosen Euro.\n\n";
				rate = value * 1.25657;
				cout << value << " SFr == " << rate << " SFr.\n\n\n\n";
				break;
			case 2:
				cout << "\nYou have chosen SFr.\n\n";
				rate = value * 1;
				cout << value << " SFr == " << rate << " SFr.\n\n\n\n";
				break;
			case 3:
				cout << "\nYou have chosen Dollars.\n\n";
				rate = value * 1.68296;
				cout << value << " SFr == " << rate << " Dollars.\n\n\n\n";
				break;
			case 4:
				cout << "\nYou have chosen Yen.\n\n";
				rate = value * 113.261;
				cout << value << " SFr == " << rate << " Yen.\n\n\n\n";
				break;
			case 5:
				cout << "\nYou have chosen Danish Krone.\n\n";
				rate = value * 9.36864;
				cout << value << " SFr == " << rate << " Danish Krone.\n\n\n\n";
				break;
			case 6:
				cout << "\nYou have chosen Chinese Yuan.\n\n";
				rate = value * 10.4010;
				cout << value << " SFr == " << rate << " Chinese Yuan.\n\n\n\n";
				break;
			}
		}

	} while (1 > 0);



	return 0;
}

