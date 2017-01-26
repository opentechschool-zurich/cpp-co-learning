#include "direction.h"
#include <gmock/gmock.h>

TEST(Direction, Unkonwn) {
    Direction d = Direction::Unknown;
    ASSERT_EQ ("Unknown", directionToString(d));
}

TEST(Direction, GoDown) {
    Direction d = Direction::GoDown;
    ASSERT_EQ ("GoDown", directionToString(d));
}

TEST(Direction, GoUp) {
    Direction d = Direction::GoUp;
    ASSERT_EQ ("GoUp", directionToString(d));
}

TEST(Direction, GoLeft) {
    Direction d = Direction::GoLeft;
    ASSERT_EQ ("GoLeft", directionToString(d));
}

TEST(Direction, GoRight) {
    Direction d = Direction::GoRight;
    ASSERT_EQ ("GoRight", directionToString(d));
}
