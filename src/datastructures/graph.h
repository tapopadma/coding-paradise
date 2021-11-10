#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<char> vc;
typedef pair<int, int> pi;
typedef pair<long long int, long long int> pll;

#define mp make_pair
#define pb push_back
#define el putchar('\n')
#define sp putchar(' ')
#define all(a) a.begin(), a.end()
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
    vi sort();
};
