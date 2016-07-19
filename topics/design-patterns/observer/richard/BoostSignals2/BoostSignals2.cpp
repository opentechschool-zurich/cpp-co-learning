#include <iostream>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;

struct HelloWorld
{
  void operator()() const {
    std::cout << "void return, no parameter" << std::endl;
  }
	void operator()(int a) const  {
    std::cout << "void return, int parameter: " << a << std::endl;
  }
	void printme(int a) const {
		std::cout << "printme member function: " << a << std::endl;
	}
};

void print_me(int a) {
  std::cout << "print_me function: " << a << std::endl;
}

int main(void) {
	// Signal with no arguments and a void return value
  boost::signals2::signal<void ()> sig;
	boost::signals2::signal<void (int)> sig_int;
  boost::signals2::signal<void (int)> sig_function;
	boost::signals2::signal<void (int)> sig_member_function;

  // Connect a HelloWorld slot
  HelloWorld hello;
  sig.connect(hello);
	sig_int.connect(hello);
	sig_function.connect(&print_me);
  //sig_member_function.connect(boost::bind(&HelloWorld::printme, int a));

  // Call all of the slots
  sig();
	sig_int(1);
	sig_function(2);
	sig_function(3);
	//sig_member_function(4);
	return 0;
}
