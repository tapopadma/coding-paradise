#include "gtest/gtest.h"
#include "next_greater.cpp"

TEST(next_greater_test, execute){
	next_greater ng;
	vi actual = ng.execute({5,1,2,5,2,6,7,2,4,1,9,8,1,1,2,2});
	vi expected = {5,2,3,5,5,6,10,8,10,10,-1,-1,14,14,-1,-1};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,actual.size()){
		EXPECT_EQ(actual[i],expected[i]);
	}
}