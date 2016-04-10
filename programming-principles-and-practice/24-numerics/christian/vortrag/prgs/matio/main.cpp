#include<iostream>
#include"Matrix.h"
#include"MatrixIO.h"

using namespace Numeric_lib; 

int main(){

  double val[] = {1.2, 3.4, 5.6, 7.8};
  Matrix<double> a(val);
  std::cout << a << std::endl; 
  
  Matrix<double,2> b(2,2);
  std::cout << "Type in a matrix of the form" << std::endl
            << "{" << std::endl
            << "{a b}" << std::endl
            << "{c d}" << std::endl
            << "}" << std::endl;
  
  std::cin >> b;
  std::cout << b << std::endl; 

  return 0;
}
