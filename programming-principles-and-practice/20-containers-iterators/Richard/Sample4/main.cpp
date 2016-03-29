#include <vector>
#include <iostream>

int main() {
    std::vector <int> myIntVector {1, 4, 8};

    //vector <int>::iterator it;
    for (auto it = myIntVector.begin(); it != myIntVector.end(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
