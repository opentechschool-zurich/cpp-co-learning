#include<iostream>
#include<string>
#include<vector>
#include "PunctStream.h"

using namespace std;

int main() {
    PunctStream ps{cin};
    ps.setWhiteSpace(";:.");
    ps.setCaseSensitive(true);

    cout << "please enter some words" << endl;
    vector<string> vs;
    /*
    for (string word; ps >> word; ) {
        vs.push_back(word);
    }
    */
    string word = "abcd";
    ps >> word;

    return 1;
}

