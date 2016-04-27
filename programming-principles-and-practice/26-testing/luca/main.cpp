#include<iostream>

#include "gtest/gtest.h"

using namespace std;


int exampleFunction() {
  return 1;
  
}


TEST(example1, Negative) {
  // This test is named "Negative", and belongs to the "example1"
  // test case.
  EXPECT_EQ(1, exampleFunction());
  EXPECT_EQ(1, exampleFunction());
  EXPECT_EQ(2, exampleFunction());
  
}


TEST(example1, Magic) {
  EXPECT_EQ(1, 1);
}


int main(int argc, char *argv[]) {
    
  testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
