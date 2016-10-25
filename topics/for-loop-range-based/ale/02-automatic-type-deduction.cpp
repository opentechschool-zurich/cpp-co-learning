#include <iostream>
#include <vector>
#include <memory>

class Abc
{
public:
    Abc(int a) : a{a} {}
    int a;
};

template<typename Range, typename Value>
void set_all_to(Range& range, const Value& value) {
    // the double & is needed for references in generic code
    for (auto&& x : range) {
        x = value;
    }
}

int main()
{

    std::cout << "loop with copy" << std::endl;
    std::vector<int> range {1,2,5,4,3};
    for (auto x : range) {
        std::cout << x << std::endl;
    }

    std::cout << "loop with copy and bool" << std::endl;
    std::vector<bool> boolRange {false, false, false};

    for (auto x : boolRange) {
        x = true;
    }

    for (auto x : boolRange) {
        std::cout << x << std::endl;
    }

    /*
    std::vector< std::unique_ptr< Abc > > abcRange;
    abcRange.emplace_back(new Abc(2));

    // fails because a unique_ptr cannot be copied out of the vector
    for (auto x : abcRange) {
        std::cout << x->a << std::endl;
    }
    */

    std::cout << "loop with auto and reference" << std::endl;

    std::vector< std::unique_ptr< Abc > > abcRange;
    abcRange.emplace_back(new Abc(2));

    for (auto& x : abcRange) {
        std::cout << x->a << std::endl;
        x->a = 4;
    }

    for (auto& x : abcRange) {
        std::cout << x->a << std::endl;
        x->a = 4;
    }

    std::cout << "use the template that sets all values to 6" << std::endl;

    std::vector<int> allInt {5,4,3,2};
    set_all_to(allInt, 6);

    for (auto& x : allInt) {
        std::cout << x << std::endl;
    }

    std::cout << "const auto reference provides read only access..." << std::endl;

    for (const auto& x : abcRange) {
        std::cout << x->a << std::endl;
        x->a = 2; // x is const, x->a is not
    }

    std::cout << "... but only to the direct element, does not protect the sub-elements" << std::endl;

    for (const auto& x : abcRange) {
        std::cout << x->a << std::endl;
    }

}
