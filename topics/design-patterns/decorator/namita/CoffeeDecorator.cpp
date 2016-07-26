/*
 * decorator.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: arktis
 */

#include "CoffeeDecorator.hpp"

using namespace meetup::opentechschool;

int main()
{
  Coffee c = Coffee();
  CreamDecorator<Coffee> cream_dec = CreamDecorator<Coffee>(c);
  cream_dec.print();
  SugarDecorator<CreamDecorator<Coffee> > sug_dec = SugarDecorator<CreamDecorator<Coffee> >(cream_dec);
  sug_dec.print();
  return 0;
}


