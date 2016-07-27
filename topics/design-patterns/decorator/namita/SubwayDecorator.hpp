/*
 * SubwayDecorator.hpp
 *
 *  Created on: Jul 26, 2016
 *      Author: arktis
 */

#ifndef OPENTECH_SCHOOL_SUBWAYDECORATOR_HPP_
#define OPENTECH_SCHOOL_SUBWAYDECORATOR_HPP_

#include <string>
#include <iostream>

namespace meetup {
namespace opentechschool {

class Bread {
public:
	Bread() {}
	virtual ~Bread() {}
	virtual std::string getDescription() = 0;
	virtual double getCost() = 0;
};

class WheatBread : public Bread {
public:
	WheatBread() : Bread() {}
	virtual ~WheatBread() {}
public:
	virtual std::string getDescription() override { return "WheatBread"; }
	virtual double getCost() override { return 2.0; }
};

class WholeGrainBread : public Bread {
public:
	WholeGrainBread() : Bread() {}
	virtual ~WholeGrainBread() {}
public:
	virtual std::string getDescription() override { return "WholeGrainBread"; }
	virtual double getCost() override { return 3.0; }
};

class ItalianBread : public Bread {
public:
	ItalianBread() : Bread() {}
	virtual ~ItalianBread() {}
public:
	virtual std::string getDescription() override { return "ItalianBread"; }
	virtual double getCost() override { return 2.5; }
};

class IngredientDecorator : public Bread {
public:
	IngredientDecorator(Bread* bread)
    : mBread(bread) {}
	virtual ~IngredientDecorator() { delete mBread; mBread=nullptr; }
	virtual  std::string getDescription() override { return mBread->getDescription(); }
	virtual double getCost() override { return mBread->getCost(); }
private:
      Bread* mBread = nullptr;
};

class CheeseDecorator: public IngredientDecorator {
public:
	CheeseDecorator(Bread* bread)
    :IngredientDecorator(bread) {}
	virtual ~CheeseDecorator() { }
	virtual  std::string getDescription()  { return "Cheese with " + IngredientDecorator::getDescription(); }
	virtual double getCost() override { return 4.0 + IngredientDecorator::getCost(); }
};

class VegDecorator: public IngredientDecorator {
public:
	VegDecorator(Bread* bread)
    :IngredientDecorator(bread) {}
	virtual ~VegDecorator() { }
	virtual  std::string getDescription()  { return "Veggies with " + IngredientDecorator::getDescription(); }
	virtual double getCost() override { return 6.0 + IngredientDecorator::getCost(); }
};

class HamDecorator: public IngredientDecorator {
public:
	HamDecorator(Bread* bread)
    :IngredientDecorator(bread) {}
	virtual ~HamDecorator() { }
	virtual  std::string getDescription()  { return "Ham with " + IngredientDecorator::getDescription(); }
	virtual double getCost() override { return 5.0 + IngredientDecorator::getCost(); }
};


} //opentechschool
} //meetup



#endif /* OPENTECH_SCHOOL_SUBWAYDECORATOR_HPP_ */
