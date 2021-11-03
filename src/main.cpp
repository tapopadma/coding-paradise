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
#define inl(n) scanf("%lld", &n)
#define in(n) scanf("%d", &n)
#define out(n) printf("%d", n);
#define outl(n) printf("%lld", n);
#define outs(s) printf("%s", s.c_str());
#define pf(s) printf(s)

#define INF64 9223372036854775807LL
#define INF 2147483647
#define mod 998244353
#define NN 2001

vector<vi> g;

void foo(int cnt,...){
	va_list ap;
	va_start(ap,cnt);
	int n=va_arg(ap,int);
	g=vector<vi>(n+1);
	for(int i=2;i<=cnt;++i){
		pi edge=va_arg(ap,pi);
		int u=edge.first;
		int v=edge.second;
		g[u].pb(v);
	}
	va_end(ap);
	for(int i=1;i<=n;++i){
		for(auto u:g[i]){
			out(u);sp;
		}
		el;
	}
	out(5);el;
	g.clear();
	out(g.size());el;
}

void solve() {
	foo(4,3,mp(1,2),mp(1,3),mp(2,3));
}

int main() {
	#ifndef ONLINE_JUDGE
		freopen("fi.in", "r", stdin);
		freopen("fo.out", "w", stdout);
		auto start = chrono::high_resolution_clock::now();
		solve();
		auto stop = chrono::high_resolution_clock::now();
		auto duration=chrono::duration_cast<chrono::milliseconds>(stop-start);
		printf("\n\n\n%6f sec",duration.count()/1000.0);
	#else
		solve();
	#endif	
	return 0;
}
