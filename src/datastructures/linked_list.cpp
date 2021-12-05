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

class linked_list_node{
public:
	int val;
	linked_list_node* next;
	linked_list_node(int v):val(v),next(NULL){}
};

class linked_list{
	linked_list_node* head;
	linked_list_node* _delete(linked_list_node*,int,pi);
public:
	linked_list():head(NULL){}
	void build(vector<pi>);
	pi detect_loop();
	void clear();
};

linked_list_node* linked_list::_delete(
	linked_list_node* cur,int i,pi cy){
	if(!cur)return NULL;
	if(i!=cy.first+cy.second-1)
		_delete(cur->next,i+1,cy);
	delete cur;
	return NULL;
}

void linked_list::clear(){
	pi cy=detect_loop();
	_delete(head,1,cy);head=NULL;
}

pi linked_list::detect_loop() {
	linked_list_node* cur1=head;
	linked_list_node* cur2=head;
	while(cur2){
		cur2=cur2->next;
		if(cur2)cur2->next;
		else break;
		cur1=cur1->next;
		if(cur1==cur2)break;
	}
	if(cur2){
		int cnt=1;cur1=cur1->next;
		while(cur1!=cur2){
			++cnt;cur1=cur1->next;
		}
		int rem=cnt,pos=1;
		cur1=head;cur2=head;
		while(rem--)cur2=cur2->next;
		while(cur1!=cur2)cur1=cur1->next,cur2=cur2->next,++pos;
		return {pos, cnt};
	}else{
		return {-1,-1};
	}
}

void linked_list::build(vector<pi> v){
	linked_list_node* nodes[v.size()];
	rep(i,0,v.size()){
		nodes[i]=new linked_list_node(v[i].first);
	}
	head=nodes[0];
	rep(i,0,v.size()){
		nodes[i]->next=(v[i].second==-1?NULL:nodes[v[i].second-1]);
	}
}