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

class binary_heap{
	int total,n;int *a;
public:
	binary_heap(int size):total(size),a(new int[size+1]),n(0){}
	void insert(int);
	int pop();
	int top();
};

int binary_heap::top(){
	return n==0?-1:a[1];
}

void binary_heap::insert(int x){
	a[++n]=x;
	for(int i=n;i/2;i/=2){
		if(a[i/2]>a[i]){
			int t=a[i/2];a[i/2]=a[i];a[i]=t;
		}else break;
	}
}

int binary_heap::pop(){
	if(n==0)return -1;
	int mn=a[1];a[1]=a[n--];
	for(int i=1;i<=n;){
		if((i*2>n||a[i]<a[i*2])
			&&(1+i*2>n||a[i]<a[1+i*2])){
			break;
		}
		int j;
		if(i*2<=n&&a[i*2]<a[i])j=i*2;
		if(1+i*2<=n&&a[1+i*2]<a[i]&&a[1+i*2]<a[i*2])j=1+i*2;
		int t=a[i];a[i]=a[j];a[j]=t;i=j;
	}
	return mn;
}