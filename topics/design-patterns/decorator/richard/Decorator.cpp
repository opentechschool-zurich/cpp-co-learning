#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Beverage  {
public:
	string description{ "Unknown Beverage" };
	double myPrice{ 0.0 };
	Beverage() {};
	Beverage(const string & desc, const double & price) {
		description = desc;
		myPrice = price;
	};
	virtual string getDescription() {
		return "From Bevrage: " + description;
	}
	virtual double cost() {
		return myPrice;
	}
};

class CondimentsDecorator : public Beverage {
private:
	Beverage myBeverage;
public:
	CondimentsDecorator(const Beverage & bev, const string & desc, const double & price) {
		myBeverage = bev;
		description = desc;
		myPrice = price;
	}
	CondimentsDecorator( const string & desc, const double & price, const CondimentsDecorator & bev) {
		myBeverage = bev;
		description = desc;
		myPrice = price;
	}
	string getDescription() {
		return "From CondimentsDecorator: " + description + " {" + myBeverage.getDescription() + "} ";
	}
	double cost() {
		return myPrice + myBeverage.cost();
	}

};

int main()
{
	Beverage espresso{ "Espresso", 1.69 };
	CondimentsDecorator sugar( espresso, "Sugar", .49 );
	CondimentsDecorator plasticCup("Small Plastic Cup", .05, sugar);
	cout << espresso.getDescription() << " costs " << espresso.cost() << endl;
	cout << sugar.getDescription() << " costs " << sugar.cost() << endl;
	cout << plasticCup.getDescription() << " costs " << plasticCup.cost() << endl;
    return 0;
}

/*
Output
From Bevrage: Espresso costs 1.69
From CondimentsDecorator: Sugar {From Bevrage: Espresso}  costs 2.18
From CondimentsDecorator: Small Plastic Cup {From Bevrage: Sugar}  costs 0.54
*/

