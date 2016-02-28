// main.cpp
#include<vector>

using namespace std;


double* get_from_jack(int* count){}

vector<double>* get_from_jill(){}

void fct(){
  int jack_count = 0;
  double* jack_data = get_from_jack(&jack_count);
  vector<double>* jill_data = get_from_jill();
  // ... process ...
  //
  delete[] jack_data;
  delete jill_data; 
  
}


int main(int argc, char *argv[])
{
    

    return 0;
}



