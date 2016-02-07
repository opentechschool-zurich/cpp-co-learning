#include<iostream>

using namespace std;

void print_array10(ostream& os, int* a){
  for (int i = 0; i < 10; ++i)
    os << a[i] << endl; 

 }


int main()
{
  int* myptr = new int[10];

  for (int i = 0; i < 10; ++i)
      cout << myptr[i] << endl; 

  print_array10(cout, myptr);

  delete[] myptr; 

  int* myptr2 = new int[11] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110}; 

  for (int i = 0; i < 11; ++i)
      cout << myptr2[i] << endl; 



  return 0;
}
