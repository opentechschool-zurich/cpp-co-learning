#pragma once
#include <sstream>

namespace non_boost {
namespace algorithm {

bool starts_with(std::string_view haystack, std::string needle)
{
    return haystack.substr(0, needle.size()) == needle;
}

void split(std::vector<std::string> &parts, std::string_view string, std::function<bool(char)> delimiterPredicate)
{
    auto it = std::find_if( string.begin(), string.end(), delimiterPredicate );
    while (it != string.end()) {
        parts.push_back(std::string(string.begin(), it));
        string = std::string(std::find_if_not(it, string.end(), delimiterPredicate), string.end());
        it = std::find_if( string.begin(), string.end(), delimiterPredicate );
	}
    if (!string.empty()) {
        parts.push_back(std::string(string));
    }
}

}
}
