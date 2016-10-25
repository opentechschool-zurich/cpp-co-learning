#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<std::string, int> wordCount;
    // wordCount.insert(std::pair<std::string, int>("hi", 5););
    wordCount["hi"] = 5;
    wordCount["ciao"] = 2;
    wordCount["ciao"] = 6; // replaces 2

    std::cout << "C++98  for loop" << std::endl;

    for (std::map<std::string, int>::iterator i = wordCount.begin(), e = wordCount.end(); i != e; ++i) {
        std::cout << i->first << std::endl;;
        std::cout << i->second << std::endl;;
    }

    std::cout << "a first c++ 11 range based loop" << std::endl;

    // the key must be const!
    // reference is for performance (or if you want to modify second)
    for (std::pair<const std::string, int>& p : wordCount) {
        std::cout << p.first << " / " << p.second << std::endl;
        if (p.first == "hi") {
            p.second = 99;
        }

    }

    std::cout << "hi is now 99" << std::endl;
    // without reference: hi should not change in the map!
    for (std::pair<const std::string, int> p : wordCount) {
        std::cout << p.first << " / " << p.second << std::endl;
        if (p.first == "hi") {
            p.second = 5;
        }
    }

    std::cout << "hi is still 99" << std::endl;
    for (std::pair<const std::string, int> p : wordCount) {
        std::cout << p.first << " / " << p.second << std::endl;
    }

    std::cout << "look ma, it's auto" << std::endl;
    for (auto& p : wordCount) {
        std::cout << p.first << " / " << p.second << std::endl;
    }

    // not yet in C++ 14
    /*
    for (auto& [word, count] : wordCount) {
        std::cout << word << " / " << count << std::endl;
    }
    */


}
