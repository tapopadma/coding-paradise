#include "gtest/gtest.h"
#include "heap.cpp"

TEST(binary_heap_test, operations){
	binary_heap b(20);
	b.insert(5);b.insert(7);b.insert(2);
	b.insert(6);b.insert(8);b.insert(2);
	b.insert(6);b.insert(9);b.insert(5);
	vi expected={2,2,5,5,6,6,7,8,9};
	rep(i,0,9){
		EXPECT_EQ(b.pop(),expected[i]);
	}
	int N=1000000;
	vi v;rep(i,0,N){
		v.pb(N-i);
	}
	binary_heap b1(N);
	vi sv=v;sort(all(sv));
	for(auto e:v)b1.insert(e);
	vi actual;
	rep(i,0,N)actual.pb(b1.pop());
	rep(i,0,N)EXPECT_EQ(actual[i],sv[i]);
}