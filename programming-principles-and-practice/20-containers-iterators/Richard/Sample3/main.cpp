#include <vector>
#include <iostream>

int main() {
    std::vector <int> myIntVector {1, 4, 8};

    //std::vector <int>::reverse_iterator it;
    for (auto it=myIntVector.rbegin(); it!=myIntVector.rend(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
