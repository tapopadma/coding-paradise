#include "gtest/gtest.h"
#include "catalan.cpp"

TEST(catalan_test, count_binary_tree){
	catalan* c;
	ASSERT_EQ(c->count_binary_tree(1),1);
	ASSERT_EQ(c->count_binary_tree(2),2);
	ASSERT_EQ(c->count_binary_tree(3),5);
	ASSERT_EQ(c->count_binary_tree(4),14);
	ASSERT_EQ(c->count_binary_tree(5),42);
	ASSERT_EQ(c->count_binary_tree(6),132);
	ASSERT_EQ(c->count_binary_tree(7),429);
	ASSERT_EQ(c->count_binary_tree(8),1430);
	ASSERT_EQ(c->count_binary_tree(9),4862);
}

TEST(catalan_test, count_binary_search_tree){
	catalan* c;
	ASSERT_EQ(c->count_binary_search_tree(1),1);
	ASSERT_EQ(c->count_binary_search_tree(2),2);
	ASSERT_EQ(c->count_binary_search_tree(3),5);
	ASSERT_EQ(c->count_binary_search_tree(4),14);
	ASSERT_EQ(c->count_binary_search_tree(5),42);
	ASSERT_EQ(c->count_binary_search_tree(6),132);
	ASSERT_EQ(c->count_binary_search_tree(7),429);
	ASSERT_EQ(c->count_binary_search_tree(8),1430);
	ASSERT_EQ(c->count_binary_search_tree(9),4862);
}