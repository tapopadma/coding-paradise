#include "graph.cpp"
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
	g.build_directed({{1,2},{2,3},{1,3},{1,4},
		{3,4},{4,5},{4,7},{5,6},{7,8},{6,9},{8,9}});
	ASSERT_EQ(g.has_cycle_directed(),false);

	g.clear(9);
	g.build_directed({{1,2},{2,3},{1,3},{1,4},{3,4},{4,5},
		{7,4},{5,6},{8,7},{6,9},{9,8}});
	ASSERT_EQ(g.has_cycle_directed(),true);

	g.clear(3);
	g.build_directed({{1,2},{2,3},{3,1}});
	ASSERT_EQ(g.has_cycle_directed(),true);

	g.clear(3);
	g.build_directed({{1,1},{2,2}});
	ASSERT_EQ(g.has_cycle_directed(),true);

	g.clear(3);
	g.build_directed({{1,2}});
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
	g.build_directed({{1,2},{2,3},{1,3}});
	vi actual=g.sort();
	vi expected={1,2,3};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,3){
		ASSERT_EQ(actual[i],expected[i]);
	}
}

TEST_F(graph_test, diameter_directed){
	graph g(8);
	g.build_directed({{1,2},{1,3},{3,4},{3,5},{4,5},{6,1},{6,5},{4,7},{7,8},{5,8}});
	ASSERT_EQ(g.diameter_directed(),5);
	g.clear(17);
	g.build_directed({{1,2},{1,3},{3,4},{3,5},{4,5},{6,1},{6,5},{4,7},
	{7,8},{5,8},{9,10},{10,11},{11,12},{11,13},{13,14},{17,16},{16,15},{15,10}});
	ASSERT_EQ(g.diameter_directed(),6);
}

TEST_F(graph_test, diameter_undirected){
	graph g(9);
	g.build_undirected({{1,2},{2,3},{3,4},{4,5},{2,6},{6,7},{6,8},{8,9}});
	ASSERT_EQ(g.diameter_undirected(),6);
}

TEST_F(graph_test, mst_prim){
	graph g(9);
	g.build_weighted_undirected({{1,2,4},{1,8,8},{2,8,11},
		{2,3,8},{8,9,7},{8,7,1},{3,9,2},{9,7,6},{3,6,4},
		{3,4,7},{7,6,2},{4,6,14},{4,5,9},{6,5,10}});
	ASSERT_EQ(g.mst_prim(),37);
	g.clear(5);
	g.build_weighted_undirected({{1,2,2},{1,4,6},{2,3,3},{2,4,8},
		{2,5,5},{3,5,7},{4,5,9}});
	ASSERT_EQ(g.mst_prim(),16);
}

TEST_F(graph_test, mst_kruskal){
	graph g(9);
	g.build_weighted_undirected({{1,2,4},{1,8,8},{2,8,11},
		{2,3,8},{8,9,7},{8,7,1},{3,9,2},{9,7,6},{3,6,4},
		{3,4,7},{7,6,2},{4,6,14},{4,5,9},{6,5,10}});
	ASSERT_EQ(g.mst_kruskal(),37);
	g.clear(5);
	g.build_weighted_undirected({{1,2,2},{1,4,6},{2,3,3},{2,4,8},
		{2,5,5},{3,5,7},{4,5,9}});
	ASSERT_EQ(g.mst_kruskal(),16);
}

TEST_F(graph_test, has_hamiltonian_cycle){
	graph g(3);
	g.build_undirected({{1,2},{2,3},{3,1}});
	ASSERT_EQ(g.has_hamiltonian_cycle(),true);
	g.clear(5);
	g.build_undirected({{1,2},{2,3},{1,4},{2,4},{2,5},{3,5},{4,5}});
	ASSERT_EQ(g.has_hamiltonian_cycle(),true);
	g.clear(4);
	g.build_directed({{1,2},{2,3},{3,4},{4,2}});
	ASSERT_EQ(g.has_hamiltonian_cycle(),false);
}

TEST_F(graph_test, dijkstra) {
	graph g(9);
	g.build_weighted_undirected({{1,2,4},{1,8,8},{2,8,11},
		{2,3,8},{8,9,7},{8,7,1},{3,9,2},{9,7,6},{3,6,4},
		{3,4,7},{7,6,2},{4,6,14},{4,5,9},{6,5,10}});
	vi actual=g.dijkstra(1);
	vi expected={0,4,12,19,21,11,9,8,14};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,9){
		EXPECT_EQ(actual[i],expected[i]);
	}
	g.clear(4);
	g.build_weighted_directed({{1,2,2},{1,3,1},{3,4,1},
		{3,2,2},{2,4,4}});
	actual=g.dijkstra(1);
	expected={0,2,1,2};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,4){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

TEST_F(graph_test,bellman_ford) {
	graph g(9);
	g.build_weighted_undirected({{1,2,4},{1,8,8},{2,8,11},
		{2,3,8},{8,9,7},{8,7,1},{3,9,2},{9,7,6},{3,6,4},
		{3,4,7},{7,6,2},{4,6,14},{4,5,9},{6,5,10}});
	vi actual=g.bellman_ford(1);
	vi expected={0,4,12,19,21,11,9,8,14};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,9){
		EXPECT_EQ(actual[i],expected[i]);
	}
	g.clear(4);
	g.build_weighted_directed({{1,2,2},{1,3,1},{3,4,1},
		{3,2,2},{2,4,4}});
	actual=g.bellman_ford(1);
	expected={0,2,1,2};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,4){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

TEST_F(graph_test,floyd_warshall) {
	graph g(9);
	g.build_weighted_undirected({{1,2,4},{1,8,8},{2,8,11},
		{2,3,8},{8,9,7},{8,7,1},{3,9,2},{9,7,6},{3,6,4},
		{3,4,7},{7,6,2},{4,6,14},{4,5,9},{6,5,10}});
	ASSERT_EQ(g.floyd_warshall(1,5),21);
	g.clear(4);
	g.build_weighted_directed({{1,2,2},{1,3,1},{3,4,1},
		{3,2,2},{2,4,4}});
	ASSERT_EQ(g.floyd_warshall(1,2),2);
}

TEST_F(graph_test,toposort_shortestpath) {
	graph g(4);
	g.build_weighted_directed({{1,2,2},{1,3,1},{3,4,1},
		{3,2,2},{2,4,4}});
	vi actual=g.toposort_shortestpath(1);
	vi expected={0,2,1,2};
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,4){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

void assert_vectors(vi actual, vi expected) {
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,actual.size()){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

TEST_F(graph_test,count_articulation_point){
	graph g(4);
	g.build_undirected({{1,2},{1,3},{2,3},{2,4},{3,4}});
	assert_vectors(g.count_articulation_point(),{});
	g.clear(5);
	g.build_undirected({{1,2},{2,3},{1,3},{3,4},{4,5}});
	assert_vectors(g.count_articulation_point(),{3,4});
	g.clear(3);
	g.build_undirected({{1,2},{2,3}});
	assert_vectors(g.count_articulation_point(),{2});
	g.clear(12);
	g.build_undirected({{1,2},{1,3},{2,4},{3,4},{3,5},{4,6},
		{4,5},{5,6},{5,7},{6,7},{6,8},{7,8},{6,9},{9,10},
		{9,11},{11,12}});
	assert_vectors(g.count_articulation_point(),{6,9,11});
	g.clear(3);
	g.build_undirected({{1,2},{1,3},{2,3}});
	assert_vectors(g.count_articulation_point(),{});
	g.clear(4);
	g.build_undirected({{1,2},{1,3},{2,3},{2,4},{3,4}});
	assert_vectors(g.count_articulation_point(),{});
}

void assert_vectors(vector<pi> actual, vector<pi> expected) {
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,actual.size()){
		EXPECT_EQ(actual[i].first,expected[i].first);
		EXPECT_EQ(actual[i].second,expected[i].second);
	}
}

TEST_F(graph_test,count_bridges){
	graph g(3);
	g.build_undirected({{1,2},{1,3}});
	assert_vectors(g.count_bridges(),{{1,2},{1,3}});
	g.clear(3);
	g.build_undirected({{1,2},{1,3},{2,3}});
	assert_vectors(g.count_bridges(),{});
	g.clear(7);
	g.build_undirected({{1,2},{1,3},{2,3},{2,7},{2,4},
		{2,5},{5,6},{4,6}});
	assert_vectors(g.count_bridges(),{{2,7}});
	g.clear(5);
	g.build_undirected({{1,2},{1,3},{2,3},{1,4},{5,4}});
	assert_vectors(g.count_bridges(),{{1,4},{4,5}});
}

TEST_F(graph_test,is_eulerian){
	graph g(6);
	g.build_undirected({{1,2},{2,3},{3,4},{2,4},{4,5},{4,6},{2,6}});
	ASSERT_EQ(g.is_eulerian(),false);
	g.clear(6);
	g.build_undirected({{1,2},{2,3},{3,4},{2,4},{4,5},{4,6},{2,6},{1,5}});
	ASSERT_EQ(g.is_eulerian(),true);
}

TEST_F(graph_test,count_scc){
	graph g(5);
	g.build_directed({{1,4},{4,5},{2,1},{3,2},{1,3}});
	vector<vi>actual=g.count_scc();
	vector<vi>expected={{1,2,3},{4},{5}};
	rep(i,0,3){
		assert_vectors(actual[i],expected[i]);
	}
}

TEST_F(graph_test,count_scc_tarjan){
	graph g(5);
	g.build_directed({{1,4},{4,5},{2,1},{3,2},{1,3}});
	vector<vi>actual=g.count_scc_tarjan();
	vector<vi>expected={{1,2,3},{4},{5}};
	rep(i,0,3){
		assert_vectors(actual[i],expected[i]);
	}
}

TEST_F(graph_test,count_max_flow_edmond_karp){
	graph g(4);
	g.build_weighted_directed({{1,2,3},{1,3,2},{2,3,5},{2,4,2},{3,4,3}});
	ASSERT_EQ(g.count_max_flow_edmond_karp(1,4),5);
	g.clear(6);
	g.build_weighted_directed({{1,2,16},{1,3,13},{2,4,12},
		{2,3,10},{3,2,4},{3,5,14},{4,3,9},{4,6,20},{5,4,7},{5,6,4}});
	ASSERT_EQ(g.count_max_flow_edmond_karp(1,6),23);
	g.clear(4);
	g.build_weighted_directed({{1,2,1},{1,3,2},{3,4,2}});
	ASSERT_EQ(g.count_max_flow_edmond_karp(1,4),2);
}

TEST_F(graph_test, find_min_cut){
	graph g(4);
	g.build_weighted_directed({{1,2,3},{1,3,2},{2,3,5},{2,4,2},{3,4,3}});
	vector<vi>actual=g.find_min_cut(1,4);
	vector<vi>expected={{1,2,3},{1,3,2}};
	rep(i,0,2)assert_vectors(actual[i],expected[i]);
	g.clear(6);
	g.build_weighted_directed({{1,2,16},{1,3,13},{2,4,12},
		{2,3,10},{3,2,4},{3,5,14},{4,3,9},{4,6,20},{5,4,7},{5,6,4}});
	actual=g.find_min_cut(1,6);
	expected={{2,4,12},{5,4,7},{5,6,4}};
	rep(i,0,3)assert_vectors(actual[i],expected[i]);
	g.clear(4);
	g.build_weighted_directed({{1,2,1},{1,3,2},{3,4,2}});
	actual=g.find_min_cut(1,4);
	expected={{1,3,2}};
	rep(i,0,1)assert_vectors(actual[i],expected[i]);
}

TEST_F(graph_test, count_max_bipartite_matching){
	graph g(12);
	g.build_directed({{1,8},{1,9},{3,7},{3,10},{4,9},{5,9},{5,10},{6,12}});
	assert_vectors(g.count_max_bipartite_matching(6,6),
		{{1,8},{3,7},{4,9},{5,10},{6,12}});
}

TEST_F(graph_test,count_max_flow_dinics){
	graph g(4);
	g.build_weighted_directed({{1,2,3},{1,3,2},{2,3,5},{2,4,2},{3,4,3}});
	ASSERT_EQ(g.count_max_flow_dinics(1,4),5);
	g.clear(6);
	g.build_weighted_directed({{1,2,16},{1,3,13},{2,4,12},
		{2,3,10},{3,2,4},{3,5,14},{4,3,9},{4,6,20},{5,4,7},{5,6,4}});
	ASSERT_EQ(g.count_max_flow_dinics(1,6),23);
	g.clear(4);
	g.build_weighted_directed({{1,2,1},{1,3,2},{3,4,2}});
	ASSERT_EQ(g.count_max_flow_dinics(1,4),2);
}

TEST_F(graph_test, tsp){
	graph g(4);
	g.build_weighted_undirected({{1,2,10},{1,4,20},{1,3,15},{2,4,25},
		{2,3,35},{3,4,30}});
	ASSERT_EQ(g.tsp(),80);
}