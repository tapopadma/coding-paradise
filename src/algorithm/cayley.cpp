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
#define NN 51

/**
 * Cayley's number: n^(n-2).
 * Question: Count the number of trees that can be made using n nodes or count
 * the number of spanning trees that can be made out of a complete graph of size n.
 * 
 * Idea: Assume root=1, we can choose i nodes out of the remaining n-1 nodes as the 
 * children of 1 in nCi ways. Now these i nodes can't have any more parents and
 * 1 can't have any more children. So now we need to count for the remaining n-1
 * nodes where i nodes will replace 1 and (n-1)-i nodes will replace n-1 nodes.
 * So rec(n,k)=SUM(nCi * rec(n-1,k-1+i)), where 0<=i<=n-k.
 */

class cayley final{
	ll fac[NN];
	ll ncr(ll,ll);
	ll rec(ll,ll);
public:
	cayley(){
		fac[0]=1;rep(i,1,NN)fac[i]=fac[i-1]*1ll*i;
	}
	int count(int);
};

ll cayley::ncr(ll n, ll r){
	return fac[n]/fac[r]/fac[n-r];
}

ll cayley::rec(ll n, ll k){
	if(n==k)return 1;
	if(k==0)return 0;
	ll ret = 0;
	rep(i,0,n-k+1){
		ret += 1ll*ncr(n-k,i)*rec(n-1,k-1+i);
	}
	return ret;
}

int cayley::count(int n) {
	return rec(n,1);
}