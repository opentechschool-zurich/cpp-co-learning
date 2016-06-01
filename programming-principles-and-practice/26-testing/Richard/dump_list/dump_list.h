#pragma once

#include <string>
#include <vector>
#include <array>

template <typename T>
std::string dump_list (T coll) {
    std::string result = "[";
    bool firsttime = true;
    for ( auto i : coll ) {
        if ( ! firsttime )
            result += ", ";
        else
            firsttime = false;
        result += std::to_string(i);
    }
    result += "]";
    return result;
}
