#include "stdafx.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

map<string, int> countWords(string inputText)
{
	map<string, int> wordMap;

	istringstream inputTextStream{ inputText };
	string s;
	while ( ! inputTextStream.eof() && inputTextStream >> s) {
		auto ret = wordMap.insert(pair<string, int>(s, 1));
		if (ret.second == false) {
			ret.first->second++;
		}
	}
	return wordMap;
}

void printWordMap(string inputText, map<string, int> wordMap) {
	cout << "---------------" << endl;
	cout << "Text: " << inputText << endl;
	cout << "Word analysis:" << endl;
	for (auto& myPair : wordMap) {
		cout << myPair.first << ":\t" << myPair.second << endl;
	}
}

int main()
{
	string text1 = "olly olly in come free";
	map<string, int> map1 = countWords(text1);
	printWordMap(text1, map1);

	string text2 = "one of each";
	map<string, int> map2 = countWords(text2);
	printWordMap(text2, map2);

	string text3 = "one fish two fish red fish blue fish";
	map<string, int> map3 = countWords(text3);
	printWordMap(text3, map3);

	string text4 = "car : carpet as java : javascript!!&@$%^&";
	map<string, int> map4 = countWords(text4);
	printWordMap(text4, map4);

	string text5 = "all the kings horses and all the kings men";
	map<string, int> map5 = countWords(text5);
	printWordMap(text5, map5);
    return 0;
}

