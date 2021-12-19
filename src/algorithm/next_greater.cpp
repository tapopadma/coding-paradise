#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<char> vc;
typedef pair<int, int> pi;
typedef pair<long long int, long long int> pll;

#define has(a,e) a.find(e)!=a.end()
#define rep(i, l, r) for(int i=l;i<r;++i)

class next_greater{
public:
	vi execute(vi a){
		int n = a.size();
		vi v(n);
		stack<int>s;
		for(int i=n-1;i>=0;--i){
			while(!s.empty()&&a[s.top()]<=a[i])s.pop();
			v[i]=s.empty()?-1:s.top();
			s.push(i);
		}
		return v;
	}
};