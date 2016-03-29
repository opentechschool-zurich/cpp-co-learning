#include <vector>
#include <iostream>

int main() {
    std::vector <int> myIntVector { 1, 4, 8 };

    for( int i=0; i < myIntVector.size(); ++i ) {
        std::cout << myIntVector[i] << " ";
    }

    return 0;
}
