#include<iostream>
#include<functional>
#include<vector>

using namespace std;


class Subject
{
public:

 Subject(int numb)
   : v{numb}, views(0) {};

  void register_func(function<void(int)> func){
    views.push_back(func)
  }

private:
  vector<function<void(int)>> views; 
  int v; 

};



class View
{
public:
  View();
  virtual ~View();
};



int main()
{

  return 0;
}
