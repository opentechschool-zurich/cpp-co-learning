#include <iostream>
#include "sq_area.cpp"
#include "circ_area.cpp"
#include "rec_area.cpp"
#include "tri_area.cpp"

using namespace std;

int main(){
  cout<<sq_area(5.0)<<endl;
  cout<<circ_area(2)<<endl;
  cout<<rec_area(5,6)<<endl;
  cout<<tri_area(5,6)<<endl;
}

