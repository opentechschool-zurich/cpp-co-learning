#include <iostream>
#include "four_op.hpp"
#include "area.hpp"

using namespace std;

int main(){
  cout<<sq_area(5)<<endl;
  cout<<circ_area(2)<<endl;
  cout<<rec_area(5,6)<<endl;
  cout<<tri_area(5,6)<<endl;
}
