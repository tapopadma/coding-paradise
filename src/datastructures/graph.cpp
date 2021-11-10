#include "graph.h"

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

void graph::build_undirected(vector<pi>v){
	for(auto edge: v){
		g[edge.first].push_back(edge.second);
		g[edge.second].push_back(edge.first);
	}
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

bool dfs1(int x, int px, int n, bool* vis, vector<vector<int>>g){
	vis[x]=true;
	for(int y: g[x]){
		if(y==px)continue;
		if(vis[y])return true;
		if(dfs1(y,x,n,vis,g))return true;
	}
	return false;
}

bool graph::has_cycle_undirected() {
	bool *vis=new bool[n+1];
	for(int i=1;i<=n;++i){
		vis[i]=false;
	}
	for(int i=1;i<=n;++i){
		if(vis[i])continue;
		if(dfs1(i, -1, n, vis, g))return true;
	}
	return false;
}

int f1nd(int x, int* pa){
	return pa[x]=pa[x]==x?x:f1nd(pa[x],pa);
}

bool un1on(int x, int y, int* pa){
	int xx = f1nd(x,pa);
	int yy = f1nd(y,pa);
	if(xx==yy)return true;
	pa[yy]=xx;
	return false;
}

bool graph::has_cycle_undirected_union_find() {
	int *pa=new int[n+1];
	for(int i=1;i<=n;++i){
		pa[i]=i;
	}
	for(int i=1;i<=n;++i){
		for(auto j:g[i]){
			//consider one edge once,ignore self loop.
			if(i>=j)continue;
			if(un1on(i,j,pa))return true;
		}
	}
	return false;
}

void dfs2(int x, bool* vis,stack<int>& s,vector<vi>g){
	if(vis[x])return;
	vis[x]=true;
	for(auto y:g[x]){
		dfs2(y,vis,s,g);
	}
	s.push(x);
}

vi graph::sort() {
	stack<int>s;
	bool *vis=new bool[n+1];
	rep(i,1,n+1)vis[i]=false;
	rep(i,1,n+1){
		dfs2(i,vis,s,g);
	}
	vi nodes;
	while(!s.empty()){
		nodes.pb(s.top());s.pop();
	}
	return nodes;
}