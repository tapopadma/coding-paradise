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


TEST_F(graph_test, cycle_in_undirectedgraph) {
	graph g(4);
	g.build_undirected({{1,2},{1,3},{2,4}});
	ASSERT_EQ(g.has_cycle_undirected(),false);
	ASSERT_EQ(g.has_cycle_undirected_union_find(),false);

	g.clear(6);
	g.build_undirected({{4,5},{4,6},{1,2},{2,3},{3,1}});
	ASSERT_EQ(g.has_cycle_undirected(),true);
	ASSERT_EQ(g.has_cycle_undirected_union_find(),true);

	g.clear(2);
	g.build_undirected({{1,2},{2,1}});
	ASSERT_EQ(g.has_cycle_undirected(),true);
	ASSERT_EQ(g.has_cycle_undirected_union_find(),true);
}

TEST_F(graph_test, topological_sort) {
	graph g(3);
	g.build_directed(3
		,make_pair(1,2)
		,make_pair(2,3)
		,make_pair(1,3));
	vi actual=g.sort();
	vi expected={1,2,3};
	rep(i,0,3){
		ASSERT_EQ(actual[i],expected[i]);
	}
}