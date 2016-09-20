# Variadic Templates 


 Short intro to Variaic Templates based on the video of Jason Turner: "C++ Weekly With Jason Turner - Episode 6: Intro To Variadic Templates" [https://www.youtube.com/watch?v=o1EvPhz6UNE]
 
 All examples are compiled with -std=c++14. 
 
 
 September 2016, Delf Dorn
 
***

## Normal Function Template

```cpp
template <typename T>
void print(const T& t)
{
    std::cout << t << '\n';
}

int main()
{
    print("Remember floppy disks?");
    print(8);
    print(5.25f);
    print(3.5);
    print("were popular sizes.");
}
``` 
The compiler creates internally print() functions for all types used.

 
## Variadic Templates
 
 Variadic Templates are for example a C++-ish way to support the implementation for something like printf(), scanf()

```cpp
template <typename T>
std::string to_string_impl(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

// "Zero-case" (when all parameters are eaten)
// We need this case even if it would never be called.
std::vector<std::string> to_string()
{   return {};   }

// Process one of the params, recursion on the remainding parameter
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
``` 

## Trying to Limit Recursion in a Variadic Template
 
One way to reduce the use of recursion in the example above is a tricky use of an initializer_list. Recursion often spoils resources big time. To transform a recursive algorithm to an iterative solution is often complicated. But I assume in the above example the recursive solution is quite efficient. 

```cpp
template <typename T>
void print_impl(const T &t)
{
    std::cout << t << '\n';
}

template <typename ... T>
void print(const T& ... t)
{
    (void) std::initializer_list<int>{ (print_impl(t), 0)... };
}

int main()
{
    print("Remember floppy disks?", 8, 5.25f, 3.5, "were popular sizes.");
}
``` 

## "Implementing an Interactive Game Console" by Michael König 

see [http://www.disco.ethz.ch/members/mikoenig/cppmeetup_console.7z]

I was very, very impressed at the August meeting of the C++ User Group Zurich. The solution uses variadic templates, verifies the syntax of commands and generates nice error messages, kudos Michael! 

I want to implement something similar for server jobs, for example a simple home automation solution. A stupid CLI client would send text commands via pipe or a message broker to the home automation server.

I like to remove the dependency to SFML 2.3. I prefer to use std::string in my solutions, but std::string does not offer all methods used in Michael's  example.

I assume that for my my use case recursion will be efficient.

