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

class kmp{
	string t,p;
	int n,m;
	int *lps;
public:
	kmp(string t,string p):t(t),p(p){
		n=t.length();m=p.length();
		lps=new int[m];
		lps[0]=0;
		int j=0;
		rep(i,1,m){
			if(p[j]==p[i]){
				lps[i]=++j;
			}else{
				while(j&&p[j]!=p[i])j=lps[j-1];
				if(p[j]!=p[i])lps[i]=j=0;
				else lps[i]=++j;
			}
		}
	}
	vi find(){
		vi v;
		int j=0;
		rep(i,0,n){
			if(t[i]==p[j]){
				if(j==m-1){
					v.pb(i-m+1);j=lps[j];
				}else ++j;
			}else{
				while(j&&t[i]!=p[j])j=lps[j-1];
				if(t[i]!=p[j])j=0;
				else ++j;
			}
		}
		return v;
	}
};

/** z[i]=longest prefix substring starting at i.
 * exactly O(n+m) time complexity.*/
class z{
	string t,p,pt;
	int n,m,nm;
	int *dp;
public:
	z(string t, string p){
		this->t=t;this->p=p;pt=p+'$'+t;
		n=t.length(),m=p.length(),nm=pt.length();
		dp=new int[pt.length()];
		int l=0,r=0;dp[0]=-1;
		rep(i,1,nm){
			if(i>r){
				l=r=i;int j=0;
				while(r<nm&&pt[r]==pt[j])++r,++j;--r;
				dp[i]=r-l+1;
			}else{
				int k=i-l;
				if(i+dp[k]-1<=r){
					dp[i]=dp[k];
				}else{
					int j=r-i+1;++r;
					while(r<nm&&pt[r]==pt[j])++r,++j;--r;
					dp[i]=r-i+1;
				}
			}
		}
	}
	vi find(){
		vi v;
		rep(i,m+1,nm){
			if(dp[i]>=m)v.pb(i-m-1);
		}
		return v;
	}
};

class suffix_array{
	int n;string s;
public:
	suffix_array(string s){
		this->s=s;n=s.length();
	}
	void print(vector<vi>v){
		for(auto e:v){
			out(e[0],e[1],e[2]);el;
		}
		puts("====");
	}
	vi build(){
		vector<vi>v;
		rep(i,0,n)v.pb({s[i]-'a',i+1<n?s[i+1]-'a':-1,i});
		sort(all(v),[](auto& e1,auto& e2){
			return e1[0]==e2[0]?e1[1]<e2[1]:e1[0]<e2[0];
		});
		int idx[n];
		for(int j=1;j<20;++j){
			int x = v[0][0], y = v[0][1],k=0,r=0;
			idx[v[0][2]]=0;
			for(int i=1;i<n;++i){
				idx[v[i][2]]=i;
				if(v[i][0]==x&&v[i][1]==y){
					continue;
				}
				while(k<i)v[k++][0]=r;r++;x=v[i][0],y=v[i][1];
			}
			while(k<n)v[k++][0]=r;
			rep(i,0,n){
				v[i][1]=(v[i][2]+(1<<j)<n)?v[idx[v[i][2]+(1<<j)]][0]:-1;
			}
			sort(all(v),[](auto& e1,auto& e2){
				return e1[0]==e2[0]?e1[1]<e2[1]:e1[0]<e2[0];
			});
		}
		vi res;for(auto vec:v)res.pb(vec[2]);
		return res;
	}
};