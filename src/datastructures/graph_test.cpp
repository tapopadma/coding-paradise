#include "graph.h"
#include "gtest/gtest.h"

class graph_test: public testing::Test {
protected:
	graph_test(){

	}
	~graph_test(){

	}
};

TEST_F(graph_test, cycle_in_digraph) {
	graph g(9);
	g.build_directed(11
		,make_pair(1,2)
		,make_pair(2,3)
		,make_pair(1,3)
		,make_pair(1,4)
		,make_pair(3,4)
		,make_pair(4,5)
		,make_pair(4,7)
		,make_pair(5,6)
		,make_pair(7,8)
		,make_pair(6,9)
		,make_pair(8,9));
	ASSERT_EQ(g.has_cycle_directed(),false);
	g.clear(9);
	g.build_directed(11
		,make_pair(1,2)
		,make_pair(2,3)
		,make_pair(1,3)
		,make_pair(1,4)
		,make_pair(3,4)
		,make_pair(4,5)
		,make_pair(7,4)
		,make_pair(5,6)
		,make_pair(8,7)
		,make_pair(6,9)
		,make_pair(9,8));
	ASSERT_EQ(g.has_cycle_directed(),true);
	g.clear(3);
	g.build_directed(3
		,make_pair(1,2)
		,make_pair(2,3)
		,make_pair(3,1));
	ASSERT_EQ(g.has_cycle_directed(),true);
	g.clear(3);
	g.build_directed(2
		,make_pair(1,1)
		,make_pair(2,2));
	ASSERT_EQ(g.has_cycle_directed(),true);
	g.clear(3);
	g.build_directed(1
		,make_pair(1,2));
	ASSERT_EQ(g.has_cycle_directed(),false);
}
