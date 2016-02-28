// main.cpp
#include<vector>
#include<iostream>

using namespace std;


double* get_from_jack(int* count){}

vector<double>* get_from_jill(){}

double* high(double* first, double* last){
  double h = -1;
  double* high;
  for (double* p =first; p!=last; ++p)
      if (h < *p){high = p; h = *p;}

  return high; 
}



void fct(){
  int jack_count = 0;
  double* jack_data = get_from_jack(&jack_count);
  vector<double>* jill_data = get_from_jill();

  double* jack_high = high(jack_data, jack_data+jack_count);
  

  vector<double>& v = *jill_data; 
  double* jill_high = high(&v[0], &v[0]+v.size()); 

  cout << "Jill's max: " << *jill_high << endl
       << "Jack's max: " << *jack_high << endl;


  delete[] jack_data;
  delete jill_data; 
  
}


int main(int argc, char *argv[])
{
    

    return 0;
}



