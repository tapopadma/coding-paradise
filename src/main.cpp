#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<char> vc;
typedef pair<int, int> pi;
typedef pair<long long int, long long int> pll;

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
#define NN 1048580

void solve() {
	// putenv("GTEST_FILTER=graph_test.count*");
	cout<<getenv("GTEST_FILTER");el;
}

int main() {
	#ifndef ONLINE_JUDGE
		if(READ_FROM_FILE){
			freopen("fi.in", "r", stdin);
			freopen("fo.out", "w", stdout);
			auto start = chrono::high_resolution_clock::now();
			solve();
			auto stop = chrono::high_resolution_clock::now();
			auto end_time = chrono::system_clock::to_time_t(stop);
			auto duration=chrono::duration_cast<chrono::milliseconds>(stop-start);
			printf("\n\n\n%6f sec \nat %s",duration.count()/1000.0,ctime(&end_time));
		} else {
			solve();
		}
	#else
		solve();
	#endif	
	return 0;
}