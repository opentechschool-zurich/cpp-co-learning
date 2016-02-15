// Example code for the vector structure in chapter 18.
#include<iostream>

class vector
{
  int size;
  double* elem; 

public:
  vector(int n)
    :size{n}, elem{new double[n]}
  { }; 
  vector(vector& ); // copy constructor
  vector& operator=(const vector&); //copy assignment

  vector(vector&& ); // move constructor
  vector& operator=(vector&&); // move assignment
  
  ~vector(){ delete[] elem;}; 

  double get(int n){ return elem[n];}; 
  void set(int n, double x){ elem[n] = x;}; 
  void print(std::ostream&);

};


vector::vector(vector& v)
  :size{v.size}, elem{new double[v.size]}
  {
    std::copy(v.elem, v.elem+size, elem); 
  }; 

vector& vector::operator=(vector& v){

  double* ptr = new double[v.size];
  std::copy(v.elem, v.elem+size, ptr);
  delete[] elem;
  elem = ptr;
  size = v.size; 

  return *this; 
 }

vector::vector(vector&& v)
  :size{v.size}, elem{v.elem}
   {
     v.size = 0;
     v.elem = nullptr; 
   }

vector& vector::operation=(vector&& v){
  size=v.size;
  delete[] elem;
  elem{v.elem}; 

  v.size = 0;
  v.elem = nullptr;

  return *this; 
}



void vector::print(std::ostream& is){  
  is << "{";

  for (int i = 0; i < size; ++i)
    is << elem[i] << ", ";

  is << elem[size] << "}" << std::endl;  
}; 


int main()
{
  vector v(2); 
  v.set(0, 5.5);
  v.set(1, 3.4);

  v.print(std::cout); 

  vector v2 = v; 
  v2.set(0, -1.0); 

  v = v2; 
  v.set(1,-1.0); 

  v.print(std::cout);
  v2.print(std::cout);


  return 0;
}
