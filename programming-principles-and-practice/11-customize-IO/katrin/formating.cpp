// chapter 11
//
// be shure about format

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>

using namespace std;
 

 
int main()
{
	cout << "\n ------------------ Output formating -------\n";
	cout << 1234 << "\n \t << 1234 \t Base invesible\n";
	cout << hex << 1234 << "\t hex << 1234 \t Base invesible \n";
	cout << 0x1234 << " \t 0x1234 \t Base invesible \n\n";  
	
	// Output format: showbase - 0x for hex, 0 for octal
	cout << showbase << "\t showbase output format\n";
	cout << 1234 << "\t << 1234 \t Wrong Base\n";
	cout << dec << 1234 << "\t << dec << 1234 \t Base dec has no prefix \n";
	cout << hex << 1234 << "\t hex << 1234 \t Base visible \n";
	cout << 0x1234 << " \t 0x1234 \t Base visible \n";  
	cout << 1234 << "\t << 1234 \t Wrong Base. Still hex !\n";
	cout << dec << 1234 << "\t << dec << 1234 \t Base dec has no prefix \n";
	
/*	cout << " \n------------------ Input formating -------\n";
	cout << "Please enter 4 times 1234. \n"; 
	string input, input_string_2;
	int input_int_1, input_int_2;
    cin >> input >> input_int_1 >> hex >> input_int_2 >> input_string_2;
    cout << input << "\n \t 1234 as string \n";
	cout << input_int_1 << "\t 1234 as int \n";
	cout << input_int_2 << "\t 1234 as int converted to >> hex \n";
	cout << showbase << "\t showbase format\n";
	cout << input_int_2 << "\t 4660 dez = 1234 hex \n";
	cout << input_string_2 << "\t 1234 as string converted to >> hex\n";                 */
	
/*	cout << " \n------------------ floating point -------\n";
	cout << 123.45 << "\t \t 123.45 normal \n";
	cout << 1234.567 << "\t \t 1234.567 normal \n";
	cout << 1.2345678 << "\t \t 1.2345678 normal \n";
	cout << fixed << 123.45 << "\t 123.45 as fixed \n";
	cout << fixed << 1234.567 << "\t \t 1234.567 fixed \n";
	cout << scientific << 123.45 << "\t 123.45 as scientific \n"; */
	
	
/*	cout <<"" << '|' << std::setw(10) << 23 << '|';
	cout << '|'  << std::setw(5) << 23 << '|' ;            */
	
/*	std:string orbits(„365.24 29.53“);
	std::string::size_type  size;

	// string to double
	double d_1, d_2, d_3;
	double earth = std::stod(orbits, &size);
	istringstream stream_a {earth};

	stream_a >> d_1 >> d_2;
	d_3 = std::stod(„1.345“);       */
	
	cout << "\n";
	
}
