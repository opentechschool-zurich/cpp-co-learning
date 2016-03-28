#include <vector>
#include <iostream>

int main() {
    std::vector <int> myIntVector {1, 4, 8};

    for ( const auto& element : myIntVector ) {
        std::cout << element << " ";
    }
    return 0;
}
