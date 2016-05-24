// This program will check repeated word in a sentence

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

int main() {

	cout << "Please type a sentence (Type 'Q' to quit the loop) \n";

	string previous="";  //previous word; initialized to "not a word"
	string current;		// initialize current word without default value

	while(cin>>current) {
		if(previous == current) {
				cout<<"repeated word: " << current << '\n';}
				previous = current;

		if(current == "Q") { 
				break;  //break out the loop, or ^ + D in Terminal
			}
	}

}
