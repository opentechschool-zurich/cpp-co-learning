#include<iostream>
#include<limits>

using namespace std;

int main(){

  cout << "DOUBLE_MAX:\t" << numeric_limits<int>::max() << endl
       << "DOUBLE_MIN:\t" << numeric_limits<int>::min() << endl
       << "DOUBLE_LOWEST:\t" << numeric_limits<int>::lowest() << endl; 
  // check std::numeric_limits for more :)
  return 0;
}
