//main.cpp
#include<algorithm>
#include<vector>
#include<iostream>
#include<string>

using namespace std;


int main(){
vector<int> my_vec = {2, 3, 4, 1, 0, 1};
  
auto p=find(my_vec.begin(), my_vec.end(), 1); 

cout << "p: " << &p << endl
<< "*p: " << *p << endl;


return 0;
}
