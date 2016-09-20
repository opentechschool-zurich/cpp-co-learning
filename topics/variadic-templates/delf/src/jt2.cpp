#include <iostream>

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
