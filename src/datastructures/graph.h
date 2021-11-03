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
    bool has_cycle_directed();
    void clear(int);
};
