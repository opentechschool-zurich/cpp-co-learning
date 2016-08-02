/**
 * Sandwich Decorator
 * http://simplestcodings.blogspot.ch/2013/12/decorator-design-pattern-implementation-in-cplusplus.html
 */

#include <iostream>
#include "sandwichDecorator.h"

int main()
{
    Ingredient* toast = new WheatBread();
    toast = new CheeseDecorator(toast);
    toast = new HamDecorator(toast);
    std::cout<< toast->getDescription() << ": " << toast->getCost() << std::endl;

    std::cout << "delete toast" << std::endl;
    delete toast;

    Ingredient* sandwichVerdure = new WholeGrainBread();
    sandwichVerdure = new CheeseDecorator(sandwichVerdure);
    sandwichVerdure = new VegDecorator(sandwichVerdure);

    std::cout<< sandwichVerdure->getDescription() << ": " << sandwichVerdure->getCost() << std::endl;

    Ingredient* sandwichRoyal = new HamDecorator(sandwichVerdure);
    std::cout<< sandwichRoyal->getDescription() << ": " << sandwichRoyal->getCost() << std::endl;

    std::cout << "delete sandwichRoyal" << std::endl;
    delete sandwichRoyal;
    // std::cout << "delete sandwichVerdure" << std::endl;
    // delete sandwichVerdure;
}
