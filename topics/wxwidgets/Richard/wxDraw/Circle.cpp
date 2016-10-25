#include "Circle.h"


auto Circle::getAge() -> double {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - created).count();
    return (double) ms / 1000;
}

auto Circle::isExpired() -> bool {
    return getAge() > timeToLive;
}
