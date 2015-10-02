#include <iostream>
#include <vector>
#include <climits>

class Negative_fibo { };

std::vector<int> fibo(int n) {
    if (n <= 0) {
        throw Negative_fibo{};
    }
    std::vector<int> result = {1};
    int previous = 1;
    int current = 1;

    for (int i = 0; i < n; i++) {
        result.push_back(current);
        int temp = previous;
        previous = current;
        current += temp ;
    }

    return result;
}

int max_fibo() {
    int previous = 1;
    int current = 1;

    std::cout << "max int " << INT_MAX << "\n";

    while (current > 0) {
        int temp = previous;
        previous = current;
        current += temp ;
    }
    return previous;
}

int main() {
    /*
    std::cout << "fibo: \n";
    int n = 10;
    try {
        std::vector<int> value = fibo(n);
        for (int i = 0; i < n; i++) {
            std::cout << value[i] << "\n";
        }
    } catch(Negative_fibo const & e) {
        std::cout << "negative value passed to fibonacci" << "\n";
    }
    */
    std::cout << "max fibo: "<< max_fibo() << "\n";
}
