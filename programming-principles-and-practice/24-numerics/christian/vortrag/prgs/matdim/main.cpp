#include<iostream>
#include"Matrix.h"

using namespace Numeric_lib; 

int main(){
  int n{2}, m{4};
    
  Matrix<double,2> mymat(n, m);  

  std::cout << "Rows: " << mymat.dim1() << std::endl
            << "Columns: " << mymat.dim2() << std::endl
            << "No Elements: " << mymat.size() << std::endl; 

  return 0;
}
