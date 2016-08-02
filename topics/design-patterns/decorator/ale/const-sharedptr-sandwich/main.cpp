/**
 * Sandwich Decorator
 * http://simplestcodings.blogspot.ch/2013/12/decorator-design-pattern-implementation-in-cplusplus.html
 */

#include <iostream>
#include <memory>
#include "sandwichDecorator.h"

using namespace std;

int main()
{

    shared_ptr<Ingredient> toast = make_shared<WheatBread>();
    toast = make_shared<CheeseDecorator>(toast);
    toast = make_shared<HamDecorator>(toast);
    cout<< toast->getDescription() << ": " << toast->getCost() << endl;

    cout << "delete toast" << endl;
    delete toast;

    /*
    shared_ptr<Ingredient> sandwichVerdure = make_shared<WholeGrainBread>();
    sandwichVerdure = new CheeseDecorator(sandwichVerdure);
    sandwichVerdure = new VegDecorator(sandwichVerdure);

    cout<< sandwichVerdure->getDescription() << ": " << sandwichVerdure->getCost() << endl;

    shared_ptr<Ingredient> sandwichRoyal = make_shared<HamDecorator>(sandwichRoyal);
    cout<< sandwichRoyal->getDescription() << ": " << sandwichRoyal->getCost() << endl;

    cout << "delete sandwichRoyal" << endl;
    delete sandwichRoyal;
    cout << "delete sandwichVerdure" << endl;
    delete sandwichVerdure;
    */
}
