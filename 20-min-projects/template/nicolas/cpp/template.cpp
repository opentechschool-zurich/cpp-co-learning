#include <iostream>
#include <cassert>

int main(int argc,	// Number of strings in array argv
	char *argv[],	// Array of command-line argument strings
	char *envp[])	// Array of environment variable strings
{
	std::cout << "\n arguments: \n";
	for( int count = 0; count < argc; count++ ){
        	std::cout << "  argv[" << count << "] " << argv[count] << std::endl;
	}
	return 1;
}

