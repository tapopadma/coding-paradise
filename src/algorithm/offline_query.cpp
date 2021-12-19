#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<char> vc;
typedef pair<int, int> pi;
typedef pair<long long int, long long int> pll;

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
#define out(a...) output(a);
#define outl(a...) outputl(a);
#define outs(s) printf("%s", s.c_str());
#define pf printf
#define INF64 9223372036854775807LL
#define INF 2147483647
#define mod 998244353
#define NN 200001

class offline_query{
	int n,m,block_size;
	vector<vi>queries;
	int *a;int *freq;
	int block_no(int i){
		int p=i-1;
		p/=block_size;
		return p+1;
	}
public:
	offline_query(vi v,vector<pi>v1){
		int n = v.size();block_size=(int)ceil(sqrt(n));
		a=new int[n+1];
		rep(i,1,n+1)a[i]=v[i-1];
		rep(i,0,v1.size())queries.pb({v1[i].first,v1[i].second,i});
		m=queries.size();
		freq=new int[1000000];
	}
	vi execute();
};

vi offline_query::execute(){
	sort(all(queries),[this](auto q1, auto q2){
		return block_no(q1[0])==block_no(q2[0])
			?q1[1]<q2[1]:block_no(q1[0])<block_no(q2[0]);
	});
	int distinct_count=0;
	rep(i,0,1000000)freq[i]=0;
	vi ans(m);
	int l=0,r=0;
	for(auto query:queries){
		while(r<query[1]){
			++freq[a[++r]];
			if(freq[a[r]]==1)++distinct_count;
		}
		while(r>query[1]){
			--freq[a[r]];
			if(freq[a[r]]==0)--distinct_count;
			--r;
		}
		while(l<query[0]){
			if(l){
				--freq[a[l]];
				if(freq[a[l]]==0)--distinct_count;
			}
			++l;
		}
		while(l>query[0]){
			++freq[a[--l]];
			if(freq[a[l]]==1)++distinct_count;
		}
		ans[query[2]]=distinct_count;
	}
	return ans;
}
