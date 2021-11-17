#include "graph.h"

void inputl() {}
template<typename... Arg>
void inputl(long long int& a, Arg&&... args) {
    scanf("%lld", &a);
    inputl(forward<Arg>(args)...);
}
void outputl(long long int a){printf("%lld ",a);}
template<typename... Arg>
void outputl(long long int a, Arg... args){printf("%lld ",a);outputl(args...);}
void input() {}
template<typename... Arg>
void input(int& a, Arg&&... args) {
    scanf("%d", &a);
    input(forward<Arg>(args)...);
}
void output(int a){printf("%d ",a);}
template<typename... Arg>
void output(int a, Arg... args){printf("%d ",a);output(args...);}
#define mp make_pair
#define pb push_back
#define el putchar('\n')
#define sp putchar(' ')
#define all(a) a.begin(), a.end()
#define has(a,e) a.find(e)!=a.end()
#define rep(i, l, r) for(int i=l;i<r;++i)
#define tr(a, it) for (auto it = a.begin(); it != a.end(); ++it)
#define inl(a...) long long int a;inputl(a);
#define in(a...) int a;input(a);
#define ina(a,n)for(int i=0;i<n;++i)scanf("%d",&a[i]);
#define inla(a,n)for(int i=0;i<n;++i)scanf("%lld",&a[i]);
#define out(a...) output(a);
#define outl(a...) outputl(a);
#define outs(s) printf("%s", s.c_str());
#define pf printf

#define READ_FROM_FILE true
#define INF64 9223372036854775807LL
#define INF 2147483647
#define mod 998244353
#define NN 200001

graph::graph(int n) {
	initialise(n);
}

void graph::initialise(int n){
	this->n=n;
	this->g=vector<vi>(n+1);
	this->g2=vector<vector<vi>>(n+1);
}

graph::~graph() {}

void graph::build_directed(vector<pi>v){
	for(auto edge: v){
		g[edge.first].push_back(edge.second);
	}
}

void graph::build_undirected(vector<pi>v){
	for(auto edge: v){
		g[edge.first].push_back(edge.second);
		g[edge.second].push_back(edge.first);
	}
}

void graph::build_weighted_undirected(vector<vi>v){
	for(auto edge:v){
		g2[edge[0]].push_back({edge[1],edge[2]});
		g2[edge[1]].push_back({edge[0],edge[2]});
	}
}

void graph::build_weighted_directed(vector<vi>v){
	for(auto edge:v){
		g2[edge[0]].push_back({edge[1],edge[2]});
	}
}

void graph::clear(int n) {
	this->g.clear();g2.clear();
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

/* push current node to stack after processing adjacents.
* an alternative is to store node in an array a[i] where i
* is the departure time.
*/
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

/*process nodes topologically and update each node to its max distance.*/
int graph::diameter_directed(){
	vi v = this->sort();
	int dist[n+1];
	rep(i,1,n+1)dist[i]=0;
	int mx=0;
	for(auto x:v){
		for(auto y:g[x]){
			dist[y]=max(dist[y],dist[x]+1);
			mx=max(mx,dist[y]);
		}
	}
	return mx;
}

/*way 1(default): find farthest node u from 1, find farthest node v from u.ans:(u,v).
* way 2: get top 2 farthest nodes per node.ans:max(sum of top 2).
*/
int graph::diameter_undirected(){
	int dist[n+1];rep(i,1,n+1)dist[i]=INF;
	//bfs1
	queue<int>q;q.push(1);dist[1]=0;
	int mx=0,u=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		if(dist[x]>mx){
			mx=dist[x];u=x;
		}
		for(auto y:g[x]){
			if(dist[y]>dist[x]+1){
				dist[y]=dist[x]+1;
				q.push(y);
			}
		}
	}
	rep(i,1,n+1)dist[i]=INF;
	//bfs2
	mx=0;int v=u;
	q.push(u);dist[u]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		if(dist[x]>mx){
			mx=dist[x];v=x;
		}
		for(auto y:g[x]){
			if(dist[y]>dist[x]+1){
				dist[y]=dist[x]+1;
				q.push(y);
			}
		}
	}
	return mx;
}

/*grab the node connected to current set via the smallest edge*/
int graph::mst_prim(){
	int cost[n+1];rep(i,1,n+1)cost[i]=INF;
	cost[1]=0;
	set<pi>s;rep(i,1,n+1)s.insert({cost[i],i});
	int ans=0;
	while(!s.empty()){
		pi p = *s.begin();s.erase(p);
		int x = p.second;ans+=cost[x];
		for(auto e:g2[x]){
			int y = e[0],w=e[1];
			if(cost[y]>w && s.find({cost[y],y})!=s.end()){
				s.erase({cost[y],y});
				cost[y]=w;
				s.insert({cost[y],y});	
			}
		}
	}
	return ans;
}

/*grab the smallest edge w/o cycle*/
int graph::mst_kruskal(){
	vector<vi> edges;
	rep(i,1,n+1){
		for(auto edge: g2[i]){
			if(edge[0] > i){
				edges.pb({edge[1],i,edge[0]});
			}
		}
	}
	std::sort(all(edges));
	int pa[n+1];rep(i,1,n+1)pa[i]=i;
	int ans = 0;
	for(auto edge:edges){
		int u=edge[1],v=edge[2],w=edge[0];
		if(f1nd(u,pa)!=f1nd(v,pa)){
			ans += w;
			un1on(u,v,pa);
		}
	}
	return ans;
}

bool dfs3(int x, int m,int s,vector<vector<bool>>a,int n,vector<vi> dp){
	if(dp[x][m]!=-1)return dp[x][m];
	if(__builtin_popcount(m)==n)
		return dp[x][m]=a[x][s];
	rep(y,1,n+1){
		if(a[x][y]&&((m>>(y-1))&1)==0){
			if(dfs3(y,m|(1<<(y-1)),s,a,n,dp))
				return dp[x][m]=true;
		}
	}
	return dp[x][m]=false;
}

/** Check if a path starts from u, visits each vertex exactly once,
 * arrives back at u. NP problem. O(n*2^n)*/
bool graph::has_hamiltonian_cycle(){
	vector<vi> dp(n+1);
	vector<vector<bool>>a(n+1);rep(i,1,n+1)rep(j,1,n+2)a[i].pb(false);
	rep(i,1,n+1)rep(j,0,1<<n)dp[i].pb(-1);
	rep(i,1,n+1){
		for(auto j:g[i]){
			a[i][j]=true;
		}
	}
	rep(i,1,n+1){
		rep(ii,1,n+1)rep(j,0,1<<n)dp[ii][j]=-1;
		if(dfs3(i,1<<(i-1),i,a,n,dp))return true;
	}
	return false;
}

/** Like prim's, pick the closest vertex u from source s instead
 * of another vertex v since dist[v]+x > dist[u] (true iff x>=0 
 * else dijkstra is wrong for negative w-graph) where dist id 
 * shortest distance from source s.
 * 
 * works for all non-negative weighted graph*/
vi graph::dijkstra(int source){
	int dist[n+1];rep(i,1,n+1)dist[i]=INF;
	dist[source]=0;
	set<pi>q;rep(i,1,n+1)q.insert({dist[i],i});
	while(!q.empty()){
		pi p=*q.begin();q.erase(p);
		int x=p.second;
		for(auto edge: g2[x]){
			int y=edge[0];
			int w=edge[1];
			if(q.find({dist[y],y})!=q.end()&&dist[y]>dist[x]+w){
				q.erase({dist[y],y});
				dist[y]=dist[x]+w;
				q.insert({dist[y],y});
			}
		}
	}
	vi costs;rep(i,1,n+1)costs.pb(dist[i]);
	return costs;
}

/**process every edge u-v and update dist[v]=min(dist[v],dist[u]+Wuv).
 * Do this n-1 times since the longest shortest path can have n-1 edges.
 * Works for negative w-graph since we consider each path of length
 * i at the ith step.
 * 
 * works for all graph. */
vi graph::bellman_ford(int source) {
	int dist[n+1];rep(i,1,n+1)dist[i]=INF;
	dist[source]=0;
	rep(c,1,n){
		rep(i,1,n+1){
			for(auto e:g2[i]){
				int j=e[0],w=e[1];
				dist[j]=min(dist[j],dist[i]+w);
			}
		}
	}
	vi costs;rep(i,1,n+1)costs.pb(dist[i]);
	return costs;	
}

/**works for all graph.*/
int graph::floyd_warshall(int source, int dest){
	int dist[n+1][n+1];
	rep(i,1,n+1)rep(j,1,n+1)dist[i][j]=(i==j?0:INF);
	rep(i,1,n+1){
		for(auto e:g2[i]){
			int j=e[0],w=e[1];
			dist[i][j]=w;
		}
	}
	rep(k,1,n+1)rep(i,1,n+1)rep(j,1,n+1){
		if(dist[i][k]!=INF&&dist[k][j]!=INF
			&&dist[i][k]+dist[k][j]<dist[i][j])
			dist[i][j]=dist[i][k]+dist[k][j];
	}
	return dist[source][dest];
}

void graph::convert_g2_to_g(){
	rep(i,1,n+1){
		for(auto e:g2[i]){
			int j=e[0];
			g[i].pb(j);
		}
	}
}

/** process edges of nodes sorted in topo order.
 * 
 * works only for DAG or tree.*/
vi graph::toposort_shortestpath(int source){
	int dist[n+1];rep(i,1,n+1)dist[i]=INF;
	dist[source]=0;
	convert_g2_to_g();
	vi nodes=sort();
	for(auto x: nodes){
		for(auto e:g2[x]){
			int y=e[0],w=e[1];
			if(dist[x]<INF)
				dist[y]=min(dist[y],dist[x]+w);
		}
	}
	vi costs;rep(i,1,n+1)costs.pb(dist[i]);
	return costs;
}

void dfs4(int x, int px, int &timer, 
	int* tim, int* mn, bool* yes,vector<vi>g){
	tim[x]=mn[x]=++timer;
	int disconnectedChildren=0;
	for(auto y:g[x]){
		if(y==px)continue;
		if(tim[y]==-1){
			++disconnectedChildren;
			dfs4(y,x,timer,tim,mn,yes,g);
			mn[x]=min(mn[x],mn[y]);
			if(mn[y]>=tim[x]){
				yes[x]=px!=-1;
			}
		} else {
			mn[x]=min(mn[x],tim[y]);
		}
	}
	if(px==-1)yes[x]=disconnectedChildren>1;
}

/** Articulation point is the node which if deleted disconnects a
 * connected graph.
 * Observation: (1) If the node belongs to a cycle and has an isolated component
 * adjacent to it or (2) if the node doesn't belong to a cycle and 
 * has degree > 1 then that's an articulation point.
 * 
 * Solution: store discovery time of u in tim[u] and minimum discovery time
 * of an ancestor node w that's reachable (not via parent of u)from any node v 
 * which belongs to the sub tree rooted with u in mn[u].
 * - now if max(mn[Cu])>=tim[u] where Cu is child of u then u is AP 
 * given it's not root.
 * - but if u is root then the number immediate child of u > 1 for it to be AP
 * since immediate child means it's not accessible by any other immediate child.
 * Note here in the dfs that we cover multiple children of u via just one
 * immediate child v.
 */
vi graph::count_articulation_point(){
	int timer=0;
	int tim[n+1];//discovery time of a node in dfs.
	int mn[n+1];//mn[u] is the minimum discovery time of a node w 
	// that can be reached from any node v that belongs to sub tree
	// rooted at u.
	bool yes[n+1];
	rep(i,1,n+1)tim[i]=-1,mn[i]=INF,yes[i]=false;
	dfs4(1,-1,timer,tim,mn,yes,g);
	vi ans;rep(i,1,n+1)if(yes[i])ans.pb(i);
	return ans;
}

void dfs5(int x, int px, int& timer, int* tim, int* mn,
	vector<pi>& bridges, vector<vi> g){
	tim[x]=mn[x]=++timer;
	for(auto y: g[x]){
		if(y==px)continue;
		if(tim[y] == -1){
			dfs5(y,x,timer,tim,mn,bridges,g);
			if(mn[y]>tim[x]){
				bridges.pb({x,y});
			}
			mn[x]=min(mn[x],mn[y]);
		} else {
			mn[x]=min(mn[x],tim[y]);
		}
	}
}

/** bridges are edges which when deleted disconnects a connected graph.
 * 
 * u-v is a bridge is mn[v] > tim[u].*/
vector<pi> graph::count_bridges() {
	int timer=0,tim[n+1],mn[n+1];
	rep(i,1,n+1)tim[i]=-1,mn[i]=INF;
	vector<pi>bridges;
	dfs5(1,-1,timer,tim,mn,bridges,g);
	std::sort(all(bridges));
	return bridges;
}

/** Eulerian path covers all edges of a undirected connected graph
 * exactly once.(Hamiltonian path on the other hand covers all nodes 
 * exactly once).
 * Eulerian path is a eulerian cycle if it starts and
 * ends at u. A graph is eulerian if it has eulerian cycle and 
 * semi-eulerian if it has eulerian path.
 * 
 * If all vertex have even degree then it's eulerian graph.
 * If n-2 vertex have even degree then it's semi-eulerian graph.*/
bool graph::is_eulerian(){
	rep(i,1,n+1)if(g[i].size()&1)return false;
	return true;
}

vector<vi> graph::transpose() {
	vector<vi>gt(n+1);
	rep(i,1,n+1){
		for(auto j:g[i]){
			gt[j].pb(i);
		}
	}
	return gt;
}

void dfs6(int x, vi& v, bool* vis, vector<vi>g){
	if(vis[x])return;
	vis[x]=true;v.pb(x);
	for(auto y:g[x]){
		dfs6(y,v,vis,g);
	}
}


/** SCC in a directed graph is a subgraph where all nodes are interconnected.
 * 
 * Observation 1: SCC and transpose(SCC) are both SCCs. means if subgraph 
 * is SCC then it's edge reversed version will also be SCC.
 * Observation 2: Let's represent graph G as C1->C2->C3->C4, then
 * transpose(G) will be C1<-C2<-C3<-C4. means if we get the top-sorted
 * nodes of G and process them in Gtranspose then the starting vertex of
 * Ci will only able to visit all nodes of Ci. means we will need 1 dfs
 * per each scc Ci. Each such dfs will detect each Ci in G.*/
vector<vi> graph::count_scc() {
	vector<vi>gt=transpose();
	bool vis[n+1];rep(i,1,n+1)vis[i]=false;
	vector<vi>sccs;
	for(auto x:sort()) {
		vi scc;
		dfs6(x,scc,vis,gt);
		if(!scc.empty())sccs.pb(scc);
	}
	std::sort(all(sccs));
	return sccs;
}