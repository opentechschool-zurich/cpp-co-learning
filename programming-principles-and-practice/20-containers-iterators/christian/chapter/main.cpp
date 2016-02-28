// main.cpp
#include<vector>
#include<iostream>

using namespace std;


double* get_from_jack(int* count){}

vector<double>* get_from_jill(){}

void fct(){
  int jack_count = 0;
  double* jack_data = get_from_jack(&jack_count);
  vector<double>* jill_data = get_from_jill();

  double h = -1;
  double* jack_high;
  double* jill_high;
  for (int i = 0; i<jack_count; ++i)
    if (h<jack_data[i])
      {
        jack_high = &jack_data[i];
        h = jack_data[i]; 
      }

  h = -1;
  for (int i = 0; i<jill_data->size(); ++i)
    if (h<(*jill_data)[i]){
      jill_high = &(*jill_data)[i];
      h = (*jill_data)[i]; 
    }

  cout << "Jill's max: " << *jill_high << endl
       << "Jack's max: " << *jack_high << endl;


  delete[] jack_data;
  delete jill_data; 
  
}


int main(int argc, char *argv[])
{
    

    return 0;
}



