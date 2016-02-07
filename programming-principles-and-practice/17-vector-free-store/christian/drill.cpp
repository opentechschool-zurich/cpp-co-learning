#include<iostream>

using namespace std;

int main()
{
  int* myptr = new int[10];

  for (int i = 0; i < 10; ++i)
      cout << myptr[i] << endl; 

  delete[] myptr; 

  return 0;
}
