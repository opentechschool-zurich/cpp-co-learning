#include <cassert>

#ifndef PI
#define PI 3.14
#endif

#ifndef FOUR_OP_HPP
#define FOUR_OP_HPP
  double add(double x,double y){return x+y;}
  double subtract(double x,double y){return(x-y);}
  double multiply(double x,double y){return x*y;}
  double devide(double x,double y){assert(y!=0); return x/y;}
#endif
