#include "cayley.cpp"
#include "gtest/gtest.h"

TEST(cayley_test,matches_formula){
	cayley c=cayley();
	ASSERT_EQ(c.count(3),3);
	ASSERT_EQ(c.count(4),16);
	ASSERT_EQ(c.count(5),125);
	ASSERT_EQ(c.count(6),1296);
	ASSERT_EQ(c.count(7),16807);
	ASSERT_EQ(c.count(8),262144);
}