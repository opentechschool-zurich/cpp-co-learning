#include<iostream>
#include<vector>

using namespace std;



struct Link{
      string value;
      Link* prev; // Vorgänger
      Link* succ; // Nachfolger
      Link(const string& v, Link* p = nullptr, Link* s = nullptr)  // string per reference
      :value{v},prev{p},succ{s}{}
  };

Link* insert(Link* p, Link* n){
    //input checking
    if (n == nullptr ) { return p;}
    if (p == nullptr ) { return n;}

    // .....      p        ....
    // insert n before p
    //  ...       n        p 
    //  prev      current  succ
    n->succ = p;
    if(p->prev) p->prev->succ = n;
    n->prev = p->prev;
    p->prev = n;
    return n;
}


int main()
{
  Link* norse_gods = new Link{"Thor"};
  norse_gods= insert(norse_gods, new Link{"Odin"}); //norse_gods->value <<
  std::cout << "Successor of " << norse_gods->value << " is " << norse_gods->succ->value << std::endl; 

  return 0;
}
