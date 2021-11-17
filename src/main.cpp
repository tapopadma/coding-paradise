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
#define NN 200001

void solve() {
	in(t);
	while(t--){
		inl(a1,a2,a3,a4,a5);
		inl(b1,b2,b3,b4,b5);
		if(a5>b5){
			pf("No");el;continue;
		}
		b5-=a5;a5=0;
		if(a4>b4+b5){
			pf("No");el;continue;
		}
		ll mn = min(b4,a4);
		b4-=mn;a4-=mn;
		b5-=a4;b1+=a4;a4=0;
		if(a3>b3+b4+b5){
			pf("No");el;continue;
		}
		mn=min(a3,b3);
		b3-=mn;a3-=mn;
		mn=min(a3,b5);
		a3-=mn;b5-=mn;b2+=mn;
		b4-=a3;b1+=a3;a3=0;
 
		if(b2+b3+b4*2ll+b5*2ll<a2){
			pf("No");el;continue;
		}
		pf(b1+b2*2ll+b3*3ll+b4*4ll+b5*5ll-a2*2ll>=a1?"Yes":"No");el;
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