#include "tree.h"

#include "gtest/gtest.h"

class tree_test: public testing::Test {
protected:
	tree_test(){

	}
	~tree_test(){

	}
};

TEST_F(tree_test, does_nothing) {
	int k=4;
	ASSERT_EQ(4,k);
}
