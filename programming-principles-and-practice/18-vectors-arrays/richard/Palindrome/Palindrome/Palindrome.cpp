#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


bool isNotAlpha(char c) {
	return ! isalpha(c);
}


bool isPalindrome(const string word) {
	string lowercasedWord = word;
	lowercasedWord.erase(remove_if(lowercasedWord.begin(), lowercasedWord.end(), isNotAlpha), lowercasedWord.end());
	transform(lowercasedWord.begin(), lowercasedWord.end(), lowercasedWord.begin(), tolower);

	string reversedWord = lowercasedWord;
	transform(reversedWord.rbegin(), reversedWord.rend(), reversedWord.begin(), tolower);
	
	return lowercasedWord == reversedWord;
}

void analysePalindrome(const string text) {
	cout << "The text \"" << text << "\" "
		<< (isPalindrome(text) ? "is" : "is not") 
		<< " a Palindrome" << endl;
}

int main()
{
	analysePalindrome("Anna");
	analysePalindrome("Mountain");
	analysePalindrome("As I pee, sir, I see Pisa!");
	analysePalindrome("Are we not drawn onward, we few, drawn onward to new era ?");
	analysePalindrome("Are we not pure ? \"No sir!\" Panama's moody Noriega brags.\"It is garbage!\"");
    return 0;
}

