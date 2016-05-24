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

  cout << &p1 << ", " << p1 << endl; 

  int myarray[7] {1, 2, 4, 8, 10, 12, 14};

  int& p2 = myarray[0]; 

  cout << ".............................\n";  
  cout << &p2 << endl << p2 << endl;
  cout << ".............................\n";   
  print_array(cout, &p2, 7);
  cout << ".............................\n";   

  int* p3 = &p2; 
  print_array(cout, p3, 7);
  cout << ".............................\n";   

  p2 = p1;
  //&p2 = p3; 

  cout << p1 << ", " << &p1 << endl;

  
  return 0;
}
