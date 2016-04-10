#include<iostream>
#include<limits>

using namespace std;

int main(){

  cout << "DOUBLE_MAX:\t" << numeric_limits<double>::max() << endl
       << "DOUBLE_MIN:\t" << numeric_limits<double>::min() << endl
       << "DOUBLE_LOWEST:\t" << numeric_limits<double>::lowest() << endl; 
  // check std::numeric_limits for more :)
  return 0;
}
