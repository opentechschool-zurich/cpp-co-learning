#include<iostream>
#include<complex>

using namespace std;

int main(){

  complex<double> mynumber(2,1);
  cout << mynumber << endl
       << "Real part: " << real(mynumber) << endl
       << "Imag. part: " << imag(mynumber) << endl;

  return 0;
}
