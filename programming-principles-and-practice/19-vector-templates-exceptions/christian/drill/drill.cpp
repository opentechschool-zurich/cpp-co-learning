// drill.cpp
#include<iostream>
#include<string>

using namespace std;



template <typename T>
struct S
{
  T val;

  S(T arg) :val{arg} {};

  T read(){return val;}; 

  T& get(){return val;}; 
};





int main(int argc, char *argv[])
{
  S<double> doubleS{5.5}; 
  S<int> intS {5};
  S<char> charS {'d'};
  S<string> stringS = {"Hello"};
  

  cout << "The value of doubleS is " << doubleS.read() << endl;
  cout << "The value of intS is " << intS.read() << endl;
  cout << "The value of charS is " << charS.read() << endl;
  cout << "The value of stringS is " << stringS.read() << endl;
  cout << "The value of doubleS is " << doubleS.read() << endl;

  int& a = intS.get(); 
  string& b = stringS.get(); 
  
  return 0;
}
