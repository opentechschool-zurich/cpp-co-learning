#include <iostream>
#include <vector>
#include <cmath>

class Negative_delta { };

std::vector<double> solve_quadratic(double a, double b, double c) {
    std::vector<double> result {0.0, 0.0};
    double delta = std::pow(b, 2) - (4 * a * c);
    if (delta < 0) {
        throw Negative_delta{};
    }
    double sqrt_delta = std::sqrt(delta);
    result[0] = (-b + sqrt_delta) / (2 * a);
    result[1] = (-b - sqrt_delta) / (2 * a);
    return result;    
}

int main() {
    std::vector<double> value;
    try {
        value = solve_quadratic(1, 2, 3);
        std::cout << value[0] << ", " << value[1] << "\n";
    } catch(Negative_delta const & e) {
        std::cout << "negative delta value" << "\n";
    }
    try {
        value = solve_quadratic(3, 20, 3);
        std::cout << value[0] << ", " << value[1] << "\n";
    } catch(Negative_delta const & e) {
        std::cout << "negative delta value" << "\n";
    }

    std::cout << "second one" << "\n";

    try {
        value = solve_quadratic(1, 2, 3);
        std::cout << value[0] << ", " << value[1] << "\n";
        value = solve_quadratic(3, 20, 3);
        std::cout << value[0] << ", " << value[1] << "\n";
    } catch(Negative_delta const & e) {
        std::cout << "negative delta value" << "\n";
    }
}
