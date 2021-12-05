#include "gtest/gtest.h"
#include "linked_list.cpp"

TEST(linked_list_test,detect_loop){
	linked_list l;
	l.build({{1,-1}});
	pi expected={-1,-1};
	ASSERT_EQ(l.detect_loop(),expected);
	l.clear();l.build({{1,1}});
	expected={1,1};
	ASSERT_EQ(l.detect_loop(),expected);
	l.clear();l.build({{1,2},{2,3},{3,2}});
	expected={2,2};
	ASSERT_EQ(l.detect_loop(),expected);
	l.clear();l.build({{1,2},{2,3},{3,4},{4,5},{5,2}});
	expected={2,4};
	ASSERT_EQ(l.detect_loop(),expected);
	l.clear();l.build({{1,2},{2,3},{3,4},{4,5},{5,1}});
	expected={1,5};
	ASSERT_EQ(l.detect_loop(),expected);
}