#include <iostream>

using namespace std;

class PalindromChecker
{
public:
  int sz;
  char *s;

//  PalindromChecker();
  explicit PalindromChecker(int size, char [] name)
  : sz{size}, s{new char[size]}
  { 
    copy(name, name+sz, s);
  }
  
  PalindromChecker(const PalindromChecker& copyFrom)
  : sz{copyFrom.sz}, s{new char[copyFrom.sz]}
  {
    copy(copyFrom.s, copyFrom.s+sz, s);
  }
  
  PalindromChecker& operator=(PalindromChecker& copyFrom)
  {
    char *temp = new char[copyFrom.sz];
    sz = copyFrom.sz;
    copy(copyFrom.s, copyFrom.s+sz, temp);
    delete[] s;
    s = temp;
    
    return *this;
  }
  
  PalindromChecker(PalindromChecker&& moveFrom)
   : sz{moveFrom.sz}, s{moveFrom.s}
  {
    moveFrom.sz = 0;
    moveFrom.s = nullptr;
  }
  
  PalindromChecker& operator=(PalindromChecker&& moveFrom)
  {
    delete[] s;
    
    sz = moveFrom.sz;
    s = moveFrom.s;
    
    moveFrom.sz = 0;
    moveFrom.s = nullptr;
    
    return *this; 
  }
  
  bool is_palindrome ()
  {
    int first = 0;
    int last = sz-1;
    
    while (first < last) {
      if (s[first] != s[last]) return false;
      ++first;
      --last;
    }
    return true;
  }  
  
};






int main() 
{
  PalindromChecker first {4, "anna"};
  if ( first.is_palindrome() ) 
  {
    cout << "Yeah it is a palindrom"; 
  }
  
  
  return 0;
}