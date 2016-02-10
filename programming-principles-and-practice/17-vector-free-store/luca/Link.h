#include <string>

using namespace std;

class Link {
public:
  string god;
  Link* prev;
  Link* succ;
  
  Link (const string &god, Link* p = nullptr, Link* s = nullptr) 
  : god{god}, prev{p}, succ{s}
    {}
  
};