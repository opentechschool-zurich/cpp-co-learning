#include "gtest/gtest.h"

#include "sumnumbers.cpp"

TEST (testsumofnumbers, sum12and13) {
	EXPECT_EQ (25, sumnumbers(12,13));
}

TEST (testsumofnumbers, sum10and12) {
	EXPECT_EQ (22, sumnumbers(10,12));
}
