#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
std::string to_string_impl(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

// The 0-th (zero) case (when all parameters are eaten)
std::vector<std::string> to_string()
{
    return {};
}

// Process one of the params, recusion on the remainding parameter
template <typename P1, typename ... Param>
std::vector<std::string> to_string(const P1 &p1, const Param& ... param)
{
    // Process the first parameter
    std::vector<std::string> s;
    s.push_back(to_string_impl(p1));
    // Process the rest with recursive call
    const auto remainder = to_string(param...);
    s.insert(s.end(), remainder.begin(), remainder.end());
    return s;
}

int main()
{
    const auto vec = to_string("Remember floppy disks?", 8, 5.25f, 3.5, "were popular sizes.");

    for (const auto &o : vec)
    {
        std::cout << o << '\n';
    }
}
