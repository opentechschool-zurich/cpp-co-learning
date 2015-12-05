#include<iostream>
#include<string>
#include<vector>

#include <algorithm>

#include "PunctStream.h"

using namespace std;

int main() {
    PunctStream ps{cin};
    ps.setWhiteSpace(";:.,");
    ps.setCaseSensitive(true);

    cout << "please enter some words (ctrl-d on an empty line to terminate)" << endl;
    vector<string> vs;
    for (string word; ps >> word; ) {
        vs.push_back(word);
    }
    sort(vs.begin(), vs.end());
    for (int i = 0; i < vs.size(); i++) {
        if (i == 0 || vs[i] != vs[i - 1]) {
            cout << vs[i] << endl;
        }
    }
    return 1;
}

