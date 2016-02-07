#include<iostream>
#include<vector>

using namespace std;

void print_array10(ostream& os, int* a){
  for (int i = 0; i < 10; ++i)
    os << a[i] << endl; 

 }

void print_array(ostream& os, int* a, int n){
  for (int i = 0; i < n; ++i)
    os << a[i] << endl; 
 }

void print_vector(ostream& os, vector<int> a){
  for (int i = 0; i < a.size(); ++i)
    os << a[i] << endl; 
 }




int main()
{

  int myint {7};
  int& p1 = myint; 


  return 0;
}
