#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

int main() {
    string iname{"numbers.csv"};
    ifstream ist {iname};
    if (!ist) throw ios_base::failure("can't open input file "+iname);

    int sum{0};
    int value;
    while (ist >> value) {
        sum += value;
    }
    cout << sum << endl;;
}
