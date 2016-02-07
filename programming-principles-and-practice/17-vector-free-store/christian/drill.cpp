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
  int* myptr = new int[10];

  for (int i = 0; i < 10; ++i)
      cout << myptr[i] << endl; 

  print_array10(cout, myptr);

  delete[] myptr; 

  // 6.
  int* myptr2 = new int[11] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110}; 

  for (int i = 0; i < 11; ++i)
      cout << myptr2[i] << endl; 

  delete[] myptr2;

  // 8
  int* myptr3 = new int[20];
  for (int i = 100; i < 120; ++i)
    myptr3[i-100] = i;
    
  
  print_array(cout, myptr3, 20); 

  delete[] myptr3;
  
  vector<int> myvec1(10);
  vector<int> myvec2(11);
  vector<int> myvec3(20);

  for (int i = 0; i < myvec1.size(); ++i)
    myvec1[i] = 100+i; 

  for (int i = 0; i < myvec2.size(); ++i)
    myvec2[i] = 100+i; 

  for (int i = 0; i < myvec3.size(); ++i)
    myvec3[i] = 100+i; 

  print_vector(cout, myvec1);
  print_vector(cout, myvec2);
  print_vector(cout, myvec3);

  return 0;
}
