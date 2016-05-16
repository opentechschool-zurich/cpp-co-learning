#include "gtest/gtest.h"

#include "multnumbers.h"

TEST (testmultnumbers, mult2and4) {
	EXPECT_EQ (8, multnumbers(2,4));
}

TEST (testmultnumbers, mult10and12) {
	EXPECT_EQ (120, multnumbers(10,12));
}
