#include<iostream>
#include"Matrix.h"

using namespace Numeric_lib; 

int main(){
  int n{2};
  int m{4};
    
  Matrix<double,2> mymat(n, m);  // 2 - dim. matrix 
    
  mymat(1,2) = 2.0;              // 2,3 - element! 
  mymat(0,1) = 4.2;              // 1,1 - element! 
  double elem12 = mymat[0][1]; 
  std::cout << elem12 << std::endl;

  return 0;
}
