#include<bits/stdc++.h>
using namespace std;

class graph final {
private:
    vector<vector<int>>g;
    int n;
    bool dfs(int, bool *, bool *);
    void initialise(int);
public:
	graph(int);
	virtual ~graph();
    void build_directed(int,...);
    void build_undirected(vector<pair<int,int>>);
    bool has_cycle_directed();
    void clear(int);
    bool has_cycle_undirected();
    bool has_cycle_undirected_union_find();
};
