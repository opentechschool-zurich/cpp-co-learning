#include<iostream>

using namespace std;

class ChocolateBoiler{

public:

  static ChocolateBoiler* get_instance();  

  virtual ~ChocolateBoiler(){
    delete unique_instance;
  };

  void fill();
  void drain();
  void boil(); 
  bool is_empty(){return empty;};
  bool is_boiled(){return boiled;}; 


private:
  ChocolateBoiler()
    : empty{true}, boiled{false}{};

  bool empty;
  bool boiled;
  static ChocolateBoiler* unique_instance; 
};

ChocolateBoiler* ChocolateBoiler::unique_instance = nullptr;

ChocolateBoiler* ChocolateBoiler::get_instance(){
  if (!unique_instance)
      unique_instance = new ChocolateBoiler(); 
  
  return unique_instance; 
}

void ChocolateBoiler::fill(){
  if (is_empty()){
      empty = false;
      boiled = false;
      cout << "gluck, gluck, gluck, ..." << endl; 
    }
}

void ChocolateBoiler::drain(){
  if (!is_empty() && is_boiled()){
    empty = true;
    cout << "flussssccchhh....." << endl; 
  }
}

void ChocolateBoiler::boil(){
  if (!is_empty()){
    boiled = true;
    cout << "blub, blub, blub, ..." << endl; 
  }
}


int main(){

  ChocolateBoiler* my_boiler = ChocolateBoiler::get_instance();

  my_boiler->fill();
  my_boiler->boil();
  my_boiler->drain();

  ChocolateBoiler* my_boiler2 = ChocolateBoiler::get_instance();
  
  my_boiler->fill();
  my_boiler2->boil();

  
       
  
  return 0;
}
