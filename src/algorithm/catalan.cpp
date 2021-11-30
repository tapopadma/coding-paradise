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

class catalan {
public:
	int count_binary_tree(int);
	int count_binary_search_tree(int);
};

/**
 * Like cayley we have one parent set of i nodes and one child set
 * of j nodes. Choose 1st node u from i nodes, 1-either remove it,
 * 2-or add 1 child to left or right, 3-or add 2 child.
 * 
 * Alternate: f(n)=sum(f(i)*f(n-i-1)), 0<=i<=n.
 */
int rec(int i, int j){
	if(i<0||j<0)return 0;
	if(j==0)return 1;
	if(i==0)return 0;
	return rec(i-1,j)+2*rec(i,j-1)+rec(i+1,j-2);
}

int catalan::count_binary_tree(int n){
	return rec(1, n-1);
}

/** choose 1 of the n nodes as root & process for left,right.*/
int rec1(int n) {
	if(n==0)return 1;
	int ret = 0;
	rep(i,0,n)ret+=rec1(i)*rec1(n-i-1);
	return ret;
}

int catalan::count_binary_search_tree(int n){
	return rec1(n);
}