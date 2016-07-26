/*
 * SubwayDecorator.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: arktis
 */
#include "SubwayDecorator.hpp"

using namespace meetup::opentechschool;

int main() {
	Bread* sandwich = new CheeseDecorator(new WholeGrainBread());
	sandwich = new VegDecorator(sandwich);
	Bread* x = new HamDecorator(new IngredientDecorator(sandwich));
	Bread* y = new HamDecorator(sandwich);
	std::cout<<x->getDescription()<<": "<<x->getCost()<<std::endl;
	std::cout<<y->getDescription()<<": "<<y->getCost()<<std::endl;

	return 0;
}



