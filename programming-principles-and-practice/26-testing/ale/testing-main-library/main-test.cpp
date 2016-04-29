#include "numbers.h"
#include "gtest/gtest.h"

TEST (SumOfIntTest, PositiveNos) { 
    EXPECT_EQ (4, numbers::sum_of_int (2, 2));
    EXPECT_EQ (2, numbers::sum_of_int (2, 0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

