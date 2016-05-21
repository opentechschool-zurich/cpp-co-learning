// main.cpp
#include<vector>
#include<iostream>

using namespace std;


double* get_from_jack(int* count){}

vector<double>* get_from_jill(){}

double* high(double* first, double* last){

  double max_val = *first;
  double* p2max_val = first;
  for (double* p =first; p!=last; ++p){
    if (max_val < *p){
      p2max_val = p;
      max_val = *p;
    }
  }

  return p2max_val; 
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
  vector<double> mydat{2.0, 1.0, 2.5, -3.0, 4.0};

  double* highest_val = high(&mydat[0], &mydat[5]);
   
    cout << "The highest val is: " << *highest_val
         << endl; 

  return 0;
}



