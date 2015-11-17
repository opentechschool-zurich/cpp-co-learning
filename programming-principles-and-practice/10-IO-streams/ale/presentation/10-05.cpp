#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;
 
struct Reading {
    int hour;
    double temperature; // in Fahrenheit
};
 
int main()
{
    cout << "Please enter input file name: ";
    string iname;
    cin >> iname;
    ifstream ist {iname};
    if (!ist) throw ios_base::failure("can't open input file "+iname);
 
    string oname;
    cout << "Please enter name of output file: ";
    cin >> oname;
    ofstream ost {oname};
    if (!ost) throw ios_base::failure("can't open output file "+oname);
 
    vector<Reading> temps; // store the readings here
    int hour;
    double temperature;
    while (ist >> hour >> temperature) {
        if (hour < 0 || 23 <hour) throw range_error("hour out of range");
        temps.push_back(Reading{hour,temperature});
    }
 
    for (int i=0; i<temps.size(); ++i)
        ost << '(' << temps[i].hour << ','
            << temps[i].temperature << ")\n";
}
