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
    {
    shared_ptr<Ingredient> toast = make_shared<WheatBread>();
    toast = make_shared<CheeseDecorator>(toast);
    toast = make_shared<HamDecorator>(toast);
    cout << "toast:" << endl;
    cout<< toast->getDescription() << ": " << toast->getCost() << endl;
    }
    cout << " toast deleted" << endl;

    shared_ptr<Ingredient> sandwichVerdure = make_shared<WholeGrainBread>();
    sandwichVerdure = make_shared<CheeseDecorator>(sandwichVerdure);
    sandwichVerdure = make_shared<VegDecorator>(sandwichVerdure);


    {
    shared_ptr<Ingredient> sandwichRoyal = make_shared<HamDecorator>(sandwichVerdure);
    cout << "sandwichRoyal:" << endl;
    cout<< sandwichRoyal->getDescription() << ": " << sandwichRoyal->getCost() << endl;
    }
    cout << "sandwichRoyal deleted" << endl;

    cout << "sandwichVerdure:" << endl;
    cout<< sandwichVerdure->getDescription() << ": " << sandwichVerdure->getCost() << endl;
    cout<< (*sandwichVerdure).getDescription() << ": " << sandwichVerdure->getCost() << endl;

    cout << "sandwichVerdure will be deleted at the of the program" << endl;
}
