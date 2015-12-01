#include<iostream>
#include<string>
#include<vector>

#include<istream>
#include<sstream>
#include <algorithm>
#include <exception>

#include "PunctStream.h"

using namespace std;

int main() {
    PunctStream ps{cin};
    ps.setWhiteSpace(";:.");
    ps.setCaseSensitive(true);

    cout << "please enter some words" << endl;
    vector<string> vs;
    for (string word; ps >> word; ) {
        vs.push_back(word);
    }

    return 1;
}

