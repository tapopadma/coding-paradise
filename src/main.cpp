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
#define NN 200005

void solve() {
	in(t);while(t--){
		in(n);
		int b[n];ina(b,n);
		int p[n];ina(p,n);
		int d[n+1];rep(i,1,n+1)d[i]=-1;
		bool ok=true;
		int val=0;
		rep(i,0,n){
			int x=p[i];
			int px=b[x-1];
			if(px==x||d[px]!=-1){
				d[x]=val++;
			} else {
				ok=false;break;
			}
		}
		if(!ok){
			out(-1);el;
		} else{
			rep(i,1,n+1){
				int x=i,px=b[x-1];
				out(d[x]-d[px]);sp;
			}el;
		}
	}
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