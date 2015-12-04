#include <iostream>
#include <string>
#include "std_lib_facilities.h" 
#include "main.h"

using std::string;

int string_to_digit ( string word ) {
    if (word == "zero") { return 0; }
    if (word == "one") { return 1; }
    if (word == "two") { return 2; }
    if (word == "three") { return 3; }
    if (word == "four") { return 4; }
    if (word == "five") { return 5; }
    if (word == "six") { return 6; }
    if (word == "seven") { return 7; }
    if (word == "eight") { return 8; }
    if (word == "nine") { return 9; }
    return -1;
}
 
int main()
{
	cout << "Hello Sandra!\n\n";
        int digit = string_to_digit( "three" );
        cout << "The digit is: " << digit << "\n";
        
        const double pi = 3.14;
        double radius = 10;
        
        double umfang = 2 * pi * radius;
        cout << "Umfang: "  << umfang << "\n";
        
	return 0;
}

