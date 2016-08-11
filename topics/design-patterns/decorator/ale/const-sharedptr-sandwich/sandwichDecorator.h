/*
 * Based on arktis example created on Jul 26, 2016
 */

#ifndef SANDWICHDECORATOR_H
#define SANDWICHDECORATOR_H

#include <string>
#include <iostream>

using namespace std;

class Ingredient {
public:
	Ingredient() {}
	virtual ~Ingredient() {cout << "~I:" << endl;}
	virtual string getDescription() const = 0;
	virtual double getCost() const = 0;
};

class WheatBread : public Ingredient {
public:
	WheatBread() : Ingredient() {}
	virtual ~WheatBread() {cout << "~WB:" << getDescription() << endl;}
public:
	virtual string getDescription() const override { return "WheatBread"; }
	virtual double getCost() const override { return 2.0; }
};

class WholeGrainBread : public Ingredient {
public:
	WholeGrainBread() : Ingredient() {}
	virtual ~WholeGrainBread() {cout << "~WGB:" << getDescription() << endl;}
public:
	virtual string getDescription() const override { return "WholeGrainBread"; }
	virtual double getCost() const override { return 3.0; }
};

class ItalianBread : public Ingredient {
public:
	ItalianBread() : Ingredient() {}
	virtual ~ItalianBread() {cout << "~IB:" << getDescription() << endl;}
public:
	virtual string getDescription() const override { return "ItalianBread"; }
	virtual double getCost() const override { return 2.5; }
};

class IngredientDecorator : public Ingredient {
public:
	IngredientDecorator(const shared_ptr<const Ingredient> ingredient)
    : ingredient(ingredient) {}
	virtual ~IngredientDecorator() {cout << "~ID:" << getDescription() << endl; /*delete ingredient;*/}
	virtual  string getDescription() const override { return ingredient->getDescription(); }
	virtual double getCost() const override { return ingredient->getCost(); }
private:
      const shared_ptr<const Ingredient> ingredient;
};

class CheeseDecorator: public IngredientDecorator {
public:
	CheeseDecorator(const shared_ptr<const Ingredient> ingredient)
    :IngredientDecorator(ingredient) {}
	virtual ~CheeseDecorator() { }
	virtual  string getDescription() const override { return "Cheese with " + IngredientDecorator::getDescription(); }
	virtual double getCost() const override { return 4.0 + IngredientDecorator::getCost(); }
};

class VegDecorator: public IngredientDecorator {
public:
	VegDecorator(const shared_ptr<const Ingredient> ingredient)
    :IngredientDecorator(ingredient) {}
	virtual ~VegDecorator() {cout << "~Veg" << endl;}
	virtual  string getDescription() const override { return "Veggies with " + IngredientDecorator::getDescription(); }
	virtual double getCost() const override { return 6.0 + IngredientDecorator::getCost(); }
};

class HamDecorator: public IngredientDecorator {
public:
	HamDecorator(const shared_ptr<const Ingredient> ingredient)
    :IngredientDecorator(ingredient) {}
	virtual ~HamDecorator() { }
	virtual  string getDescription() const override { return "Ham with " + IngredientDecorator::getDescription(); }
	virtual double getCost() const override { return 5.0 + IngredientDecorator::getCost(); }
};

#endif
