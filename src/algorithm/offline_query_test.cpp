#include "gtest/gtest.h"
#include "offline_query.cpp"

void assert_vectors(vi actual, vi expected) {
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,actual.size()){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

TEST(offline_query_test, count_distinct){
	offline_query q({1, 2, 3, 1, 1, 2, 1, 2, 3, 1},
		{{1,10},{4,5},{6,8},{7,9},{8,10},{9,10}});
	assert_vectors(q.execute(),{3,1,2,3,3,2});
}