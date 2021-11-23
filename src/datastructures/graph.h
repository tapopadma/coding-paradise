#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<char> vc;
typedef pair<int, int> pi;
typedef pair<long long int, long long int> pll;

class graph final {
private:
    vector<vector<int>>g;
    vector<vector<vi>>g2;
    int n;
    int **a;
    bool dfs(int, bool *, bool *);
    void initialise(int);
    void convert_g2_to_g();
    void build_network_from_bipartite(int,int);
    void convert_to_residual_graph();
    void convert_to_residual_graph_dinics();
public:
	graph(int);
	virtual ~graph();
    void build_directed(vector<pi>);
    void build_undirected(vector<pi>);
    bool has_cycle_directed();
    void clear(int);
    bool has_cycle_undirected();
    bool has_cycle_undirected_union_find();
    vi sort();
    int diameter_undirected();
    int diameter_directed();
    int mst_prim();
    int mst_kruskal();
    void build_weighted_undirected(vector<vi>);
    bool has_hamiltonian_cycle();
    vi dijkstra(int);
    void build_weighted_directed(vector<vi>);
    vi bellman_ford(int);
    int floyd_warshall(int,int);
    vi toposort_shortestpath(int);
    vi count_articulation_point();
    vector<pi> count_bridges();
    bool is_eulerian();
    vector<vi>count_scc();
    vector<vi>transpose();
    vector<vi>count_scc_tarjan();
    int count_max_flow_edmond_karp(int, int);
    int count_max_flow_dinics(int, int);
    vector<vi> find_min_cut(int, int);
    vector<pi> count_max_bipartite_matching(int, int);
    int tsp();
};
