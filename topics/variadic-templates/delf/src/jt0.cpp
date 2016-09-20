#include <iostream>

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
    print("where popular sizes.");
}
