#include <iostream>
#include "gtest/gtest.h"

int sum_of_int(int a, int b) {
	return a + b;
}

TEST (SumOfIntTest, PositiveNos) { 
    EXPECT_EQ (4, sum_of_int (2, 2));
    EXPECT_EQ (2, sum_of_int (2, 0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
