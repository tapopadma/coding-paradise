#include "graph.h"
typedef pair<int, int> pi;

graph::graph(int n) {
	initialise(n);
}

void graph::initialise(int n){
	this->n=n;
	this->g=vector<vector<int>>(n+1);
}

graph::~graph() {}

void graph::build_directed(int cnt,...){
	va_list ap;
	va_start(ap,cnt);
	for(int i=0;i<cnt;++i){
		pi edge=va_arg(ap,pi);
		int u=edge.first;
		int v=edge.second;
		g[u].push_back(v);
	}
	va_end(ap);
}

void graph::clear(int n) {
	this->g.clear();
	initialise(n);
}

bool graph::has_cycle_directed() {
	bool *vis=new bool[n+1];
	bool *instack=new bool[n+1];
	for(int i=1;i<=n;++i){
		vis[i]=false;
		instack[i]=false;
	}
	for(int i=1;i<=n;++i){
		if(dfs(i, vis, instack))return true;
	}
	return false;
}

bool graph::dfs(int x, bool *vis, bool *instack) {
	if(instack[x])return true;
	if(vis[x])return false;
	vis[x]=true;instack[x]=true;
	for(auto y:g[x]) {
		if(dfs(y,vis,instack))return true;
	}
	instack[x]=false;
	return false;
}
