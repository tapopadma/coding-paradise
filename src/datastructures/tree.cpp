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

class avl_tree_node{
public:
	int val,height,cnt,freq;
	avl_tree_node* left;avl_tree_node* right;
	avl_tree_node(int v):val(v),height(1),cnt(1),freq(1)
				,left(NULL),right(NULL){}
	void refresh();
};

class avl_tree {
	avl_tree_node* root;
	avl_tree_node* _insert(avl_tree_node*,int);
	int _query(avl_tree_node*,int);
	avl_tree_node* _delete(avl_tree_node*,int);
	avl_tree_node* self_balance(avl_tree_node*);
	void print(avl_tree_node*);
public:
	avl_tree(){
		root=NULL;
	}
	void ins3rt(int);
	void d3lete(int);
	int get_kth_max(int);
	void clear();
};

void avl_tree_node::refresh(){
	cnt=(left?left->cnt:0)+(right?right->cnt:0)+freq;
	height=max(left?left->cnt:0,right?right->cnt:0)+1;
}

avl_tree_node* avl_tree::self_balance(avl_tree_node* root){
	if(!root)return NULL;
	if(root->left&&
	   root->left->height>(root->right?root->right->height:0)+1){

		avl_tree_node* a=root->left;
		root->left=a->right;a->right=root;
		
		root->refresh();
		a->refresh();
		return a;
	} else if(root->right&&
		root->right->height>(root->left?root->left->height:0)+1){

		avl_tree_node* a=root->right;
		root->right=a->left;a->left=root;

		root->refresh();
		a->refresh();
		return a;
	}
	return root;
}

avl_tree_node* avl_tree::_insert(avl_tree_node* root, int x){
	if(root==NULL){
		return new avl_tree_node(x);
	}
	if(root->val==x){
		root->cnt++;root->freq++;return root;
	}
	if(root->val<x){
		root->right=_insert(root->right,x);
		root->refresh();
	} else {
		root->left=_insert(root->left,x);
		root->refresh();
	}
	return self_balance(root);
}

void avl_tree::print(avl_tree_node* root){
	if(!root)return;
	print(root->left);
	rep(i,0,root->freq){out(root->val);sp;}
	print(root->right);
}

void avl_tree::ins3rt(int x){
	root=_insert(root,x);
	// print(root);el;
}

int avl_tree::_query(avl_tree_node* root, int k){
	if(!root||k>root->cnt)return -1;
	if(root->right&&root->right->cnt >= k)
		return _query(root->right,k);
	k-=(root->right?root->right->cnt:0);
	if(k<=root->freq)return root->val;
	k-=root->freq;
	return _query(root->left,k);
}

int avl_tree::get_kth_max(int k){
	return _query(root,k);
}

avl_tree_node* avl_tree::_delete(avl_tree_node* root, int x){
	if(!root)return NULL;
	if(root->val==x){
		if(root->freq>1){
			--root->cnt;--root->freq;return root;
		} else {
			if(!root->left){
				avl_tree_node* p=root->right;
				delete root;
				return self_balance(p);
			}
			if(!root->right){
				avl_tree_node* p=root->left;
				delete root;
				return self_balance(p);	
			}
			avl_tree_node* next_avl_tree_node=root->right;
			while(next_avl_tree_node->left)next_avl_tree_node=next_avl_tree_node->left;
			root->left->right=next_avl_tree_node;
			avl_tree_node* p=root->left;p->refresh();
			delete root;
			return self_balance(p);
		}
	}else if(root->val < x){
		root->right=_delete(root->right,x);
	}else{
		root->left=_delete(root->left,x);
	}
	root->refresh();
	return self_balance(root);
}

void avl_tree::d3lete(int x){
	root=_delete(root, x);
}

void avl_tree::clear(){
	while(root){
		root=_delete(root, root->val);
	}
}


class binary_tree_node{
public:
	int val;
	binary_tree_node* left;binary_tree_node* right;
	binary_tree_node(int v):val(v),left(NULL),right(NULL){}
};

class binary_tree{
	binary_tree_node* root;
	bool equals(binary_tree_node*,binary_tree_node*);
public:
	void build(vector<vi>);
	void clear();
	bool is_foldable();
	vi level_spiral_order();
	binary_tree merge_bsts(binary_tree);
	pair<binary_tree_node*,binary_tree_node*> convert_to_dll(
		binary_tree_node*);
	binary_tree_node* convert_from_dll(binary_tree_node*,
		binary_tree_node*);
	bool equals(binary_tree);
};

bool binary_tree::equals(binary_tree_node* root1, 
	binary_tree_node* root2){
	if(!root1 || !root2)
		return !root1&&!root2;
	return root1->val==root2->val
		&&equals(root1->left,root2->left)
		&&equals(root1->right,root2->right);
}

bool binary_tree::equals(binary_tree t2){
	return equals(root, t2.root);
}

pair<binary_tree_node*,binary_tree_node*> binary_tree::convert_to_dll(
	binary_tree_node* root){
	if(!root)return {NULL,NULL};
	pair<binary_tree_node*,binary_tree_node*> dll1 = 
		convert_to_dll(root->left);
	pair<binary_tree_node*,binary_tree_node*> dll2 = 
		convert_to_dll(root->right);
	if(!dll1.second){
		if(!dll2.first){
			return {root,root};
		}
		else{
			root->right=dll2.first;
			dll2.first->left=root;
			return {root,dll2.second};
		}
	}else{
		if(!dll2.first){
			dll1.second->right=root;
			root->left=dll1.second;
			return {dll1.first,root};
		}
		else{
			dll1.second->right=root;
			root->left=dll1.second;
			root->right=dll2.first;
			dll2.first->left=root;
			return {dll1.first,dll2.second};
		}
	}
}

binary_tree_node* binary_tree::convert_from_dll(
	binary_tree_node* head, binary_tree_node* tail){
	binary_tree_node* p1=head;
	binary_tree_node* p2=head;
	while(p2!=tail){
		p2=p2->right;
		if(p2!=tail)p2=p2->right;else break;
		p1=p1->right;
	}
	binary_tree_node* root1=(p1==head
		?NULL:convert_from_dll(head,p1->left));
	binary_tree_node* root2=(p1==tail?
		NULL:convert_from_dll(p1->right,tail));
	p1->left=root1;p1->right=root2;
	return p1;
}

binary_tree binary_tree::merge_bsts(binary_tree t2){
	pair<binary_tree_node*,binary_tree_node*> dll1 = 
		convert_to_dll(root);
	pair<binary_tree_node*,binary_tree_node*> dll2 = 
		convert_to_dll(t2.root);
	binary_tree_node* head1=dll1.first;
	binary_tree_node* head2=dll2.first;
	binary_tree_node* cur=NULL;
	binary_tree_node* head;
	binary_tree_node* tail;
	while(head1 || head2){
		if(!head1){
			if(cur){
				cur->right=head2;head2->left=cur;cur=cur->right;
			}else{
				cur=head2;head=cur;
			}
			head2=head2->right;
		}else if(!head2){
			if(cur){
				cur->right=head1;head1->left=cur;cur=cur->right;
			}else{
				cur=head1;head=cur;
			}
			head1=head1->right;
		}else{
			if(cur){
				if(head1->val < head2->val){
					cur->right=head1;head1->left=cur;
					cur=cur->right;head1=head1->right;
				}else{
					cur->right=head2;head2->left=cur;
					cur=cur->right;head2=head2->right;
				}	
			}else {
				if(head1->val < head2->val){
					cur=head1;head1=head1->right;head=cur;
				}else{
					cur=head2;head2=head2->right;head=cur;
				}
			}
		}
	}
	tail=cur;
	root = convert_from_dll(head, tail);
	return *this;
}

vi binary_tree::level_spiral_order(){
	if(!root)return {};
	deque<pair<binary_tree_node*,int>>q;
	q.push_back({root,0});int parity=0,pl=0;
	vi v;
	while(!q.empty()){
		pair<binary_tree_node*,int> xl;
		if(parity&1){
			if(pl!=q.back().second){
				pl=q.back().second;parity=1-parity;continue;
			}
			xl=q.back();q.pop_back();
		}else{
			if(pl!=q.front().second){
				pl=q.front().second;parity=1-parity;continue;
			}
			xl=q.front();q.pop_front();
		}
		binary_tree_node* x=xl.first;int l=xl.second;
		v.pb(x->val);
		if(l&1){
			if(x->right)q.push_front({x->right,l+1});
			if(x->left)q.push_front({x->left,l+1});
		}else{
			if(x->left)q.push_back({x->left,l+1});
			if(x->right)q.push_back({x->right,l+1});
		}
	}
	return v;
}

void _delete(binary_tree_node* root){
	if(!root)return;
	_delete(root->left);
	_delete(root->right);
	delete root;
}

void binary_tree::clear(){
	_delete(root);root=NULL;
}

void binary_tree::build(vector<vi> data){
	binary_tree_node* nodes[data.size()];
	rep(i,0,data.size()){
		nodes[i]=new binary_tree_node(data[i][0]);
	}
	rep(i,0,data.size()){
		nodes[i]->left=
			(data[i][1]==-1?NULL:nodes[data[i][1]-1]);
		nodes[i]->right=
			(data[i][2]==-1?NULL:nodes[data[i][2]-1]);
	}
	root=nodes[0];
}

bool dfs1(binary_tree_node* root1, binary_tree_node* root2){
	if(!root1&&!root2)return true;
	if(!root1||!root2)return false;
	return dfs1(root1->left,root2->right)
		&& dfs1(root1->right,root2->left);
}

bool binary_tree::is_foldable(){
	return !root || dfs1(root->left,root->right);
}

class segment_tree{
	int *T;
	int n;
	void build(int i, int l, int r, vi v){
		if(l==r){
			T[i]=v[l];return;
		}
		int m=(l+r)/2;
		build(i*2,l,m,v);
		build(1+i*2,1+m,r,v);
		T[i]=T[i*2]+T[1+i*2];
	}
public:
	segment_tree(int n){
		this->n=n;
		T=new int[4*n];
		rep(i,0,4*n)T[i]=0;
	}
	segment_tree(vi v){
		n=v.size();
		T=new int[4*n];
		build(1,1,n,v);
	}
	int query_range(int, int);
	void update_point(int,int);
	int get_kth_max(int);
};

int _get_kth_max(int i, int l, int r, int k, int* T){
	if(l==r)return l;
	int m=(l+r)/2;
	if(T[1+i*2]>=k)return _get_kth_max(1+i*2,1+m,r,k,T);
	return _get_kth_max(i*2,l,m,k-T[1+i*2],T);
}

int segment_tree::get_kth_max(int k){
	return _get_kth_max(1,1,n,k,T);
}

int _query_range(int i, int l, int r, int x, int y, int* T){
	if(x>r||y<l)return 0;
	if(x<=l&&r<=y)return T[i];
	int m=(l+r)/2;
	return _query_range(i*2,l,m,x,y,T)
			+_query_range(1+i*2,1+m,r,x,y,T);
}

int segment_tree::query_range(int x, int y){
	return _query_range(1,1,n,x,y,T);
}

void _update(int i, int l, int r, int x, int v,int *T){
	if(x>r||x<l)return;
	if(l==r){
		T[i]=v;return;
	}
	int m=(l+r)/2;
	_update(i*2,l,m,x,v,T);
	_update(1+i*2,1+m,r,x,v,T);
	T[i]=T[i*2]+T[1+i*2];
}

void segment_tree::update_point(int x, int v){
	_update(1,1,n,x,v,T);
}

class segment_tree_lazy{
	int **T;int n;
	void build(int i, int l, int r, vi v){
		if(l==r){
			T[i][0]=v[l-1];T[i][1]=0;return;
		}
		int m=(l+r)/2;
		build(i*2,l,m,v);
		build(1+i*2,1+m,r,v);
		T[i][0]=T[i*2][0]+T[1+i*2][0];
		T[i][1]=0;
	}
	void update(int,int,int,int,int,int);
	void unload(int,int,int);
	int query(int,int,int,int,int);
public:
	segment_tree_lazy(vi v){
		n=v.size();
		T=new int*[n*4];
		rep(i,0,n*4)T[i]=new int[2];
		build(1,1,n,v);	
	}
	void update(int,int,int);
	int query(int,int);
};

void segment_tree_lazy::unload(int i,int l,int r){
	T[i][0]+=(r-l+1)*T[i][1];
	if(l<r){
		T[i*2][1]+=T[i][1];T[1+i*2][1]+=T[i][1];
	}
	T[i][1]=0;
}

void segment_tree_lazy::update(int i, int l, int r,
	int x, int y, int v){
	unload(i,l,r);
	if(x>r||y<l)return;
	if(x<=l&&r<=y){
		T[i][1]+=v;
		unload(i,l,r);
		return;
	}
	int m=(l+r)/2;
	update(i*2,l,m,x,y,v);
	update(1+i*2,1+m,r,x,y,v);
	T[i][0]=T[i*2][0]+T[1+i*2][0];
}

void segment_tree_lazy::update(int x, int y, int v){
	update(1,1,n,x,y,v);
}

int segment_tree_lazy::query(int i, int l, int r, int x, int y){
	unload(i,l,r);
	if(x>r||y<l)return 0;
	if(x<=l&&r<=y){
		return T[i][0];
	}
	int m=(l+r)/2;
	return query(i*2,l,m,x,y)+query(1+i*2,1+m,r,x,y);
}

int segment_tree_lazy::query(int x, int y){
	return query(1,1,n,x,y);
}

class segment_tree_pst_node{
public:
	int l,r,val;segment_tree_pst_node* left;segment_tree_pst_node* right;
	segment_tree_pst_node(int l1,int r1,int v1)
		:l(l1),r(r1),val(v1),left(NULL),right(NULL){}
};

/** 
 * Persistent segment tree is a union of multiple version of
 * segment trees T1 u T2 u T3...Tm which stores a version after
 * each update and hence enables querying w.r.t
 * any desired version i at any time using root of Ti.
 * 
 * The total memory O(mlogn) where n is the max coverage of a
 * segment and m is the no of updates aka version.
 * adding Ti means adding logn nodes to (Ti-1 u Ti-2 u...T1).
 * 
 * Use case:Find number of elements ai in subarray [l,r] in the 
 * array a of n elements such that x<=ai<=y.
 * Just build a PST with a Ti at each position i in O(nlogn).
 * Now PST.query(r,x,y)-PST.query(l-1,x,y) is the answer in O(logn).
 */ 
class segment_tree_persistent{
	int n;vector<segment_tree_pst_node*> roots;
	segment_tree_pst_node* update(int,int,int,int,segment_tree_pst_node*);
	int query(segment_tree_pst_node*,int,int,int,int);
public:
	segment_tree_persistent(int m){
		n=m;
	}
	void update(int,int);
	int query(int,int,int);
};

segment_tree_pst_node* segment_tree_persistent::update(int l, int r,
	int x, int val, segment_tree_pst_node* prev){
	if(x>r||x<l)return prev;
	segment_tree_pst_node* cur=new segment_tree_pst_node(l,r,val);
	if(l==r)return cur;
	int m=(l+r)/2;
	cur->left=update(l,m,x,val,prev==NULL?NULL:prev->left);
	cur->right=update(1+m,r,x,val,prev==NULL?NULL:prev->right);
	cur->val=(cur->left?cur->left->val:0)
		+(cur->right?cur->right->val:0);
	return cur;
}

void segment_tree_persistent::update(int x,int val){
	segment_tree_pst_node* prev=roots.empty()?NULL:roots[roots.size()-1];
	roots.pb(update(1,n,x,val,prev));
}

int segment_tree_persistent::query(segment_tree_pst_node* root,int l, int r,
	int x, int y){
	if(x>r||y<l||!root)return 0;
	if(x<=l&&r<=y)return root->val;
	int m=(l+r)/2;
	return query(root->left,l,m,x,y)+query(root->right,1+m,r,x,y);
}

int segment_tree_persistent::query(int v,int x,int y){
	return v?query(roots[v-1],1,n,x,y):0;
}

class trie_node{
public:
	trie_node* links[26];
	bool ends;
	trie_node(){
		rep(i,0,26)links[i]=NULL;
		ends=false;
	}
};

class trie{
	trie_node* root;
	trie_node* insert(trie_node*,int,string);
	bool search(trie_node*,int,string);
	trie_node* erase(trie_node*, int, string);
public:
	trie():root(new trie_node()){}
	void insert(string);
	void erase(string);
	bool search(string);
};

trie_node* trie::insert(trie_node* root, int i, string s){
	if(i==s.length()){
		root->ends=true;
		return root;
	}
	int idx=s[i]-'a';
	if(!root->links[idx]){
		root->links[idx]=new trie_node();
	}
	root->links[idx]=insert(root->links[idx],i+1,s);
	return root;
}

void trie::insert(string s){
	root=insert(root,0,s);
}

bool trie::search(trie_node* root, int i, string s){
	if(i==s.length())return root->ends;
	int idx=s[i]-'a';
	return root->links[idx]&&search(root->links[idx],i+1,s);
}

bool trie::search(string s){
	return search(root,0,s);
}

bool is_leaf(trie_node* root){
	rep(i,0,26)if(root->links[i])return false;
	return true;
}

trie_node* trie::erase(trie_node* root, int i, string s){
	if(i==s.length()){
		root->ends=false;
		if(is_leaf(root)){
			delete root;
			return NULL;
		}
		return root;
	}
	int idx=s[i]-'a';
	if(!root->links[idx])return root;
	root->links[idx]=erase(root->links[idx],i+1,s);
	if(is_leaf(root)&&!root->ends&&i>0){
		delete root;return NULL;
	}
	return root;
}

void trie::erase(string s){
	root=erase(root,0,s);
}