#include "gtest/gtest.h"
#include "triangle_type.h"

TEST(triangletests, isosceles1) {
	EXPECT_EQ("Isosceles", triangle_type(5, 5, 3));
}

TEST(triangletests, isosceles2) {
	EXPECT_EQ("Isosceles", triangle_type(3, 5, 5));
}

TEST(triangletests, equilateral) {
	EXPECT_EQ("Equilateral", triangle_type(5,5,5));
}

TEST(triangletests, scalene1) {
	EXPECT_EQ("Scalene", triangle_type(3, 4, 5));
}

TEST(triangletests, notriangle1) {
	EXPECT_EQ("Not a triangle", triangle_type(1, 4, 5));
}

TEST(triangletests, notriangle2) {
	EXPECT_EQ("Not a triangle", triangle_type(5, 3, 1));
}

TEST(triangletests, notriangle3) {
	EXPECT_EQ("Not a triangle", triangle_type(0, 0, 0));
}

TEST(triangletests, notrianglenegative1) {
	EXPECT_EQ("Negative Number not allowed!", triangle_type(-4, 4, 0));
}

TEST(triangletests, notrianglenegative2) {
	EXPECT_EQ("Negative Number not allowed!", triangle_type(-4, -5, -3));
}

TEST(triangletests, notrianglenegative3) {
	EXPECT_EQ("Negative Number not allowed!", triangle_type(-4, -5, 8));
}