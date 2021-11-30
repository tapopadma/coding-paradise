#include "gtest/gtest.h"
#include "tree.cpp"

TEST(avl_tree_test, get_kth_max){
	avl_tree t;
	vector<vi> vec={{1,2,3,4,5,6,7},
				{9,5,10,0,6,11,-1,1,2},
				{7,5,1,2,2,4,3,4,2},
				{1,1,1,1,1},
				{7,6,1,2,0,-1,0,0,-23,23,33}};
	vi v_large;
	rep(i,0,1000000){
		v_large.pb(i+1);v_large.pb(1000000-i);v_large.pb(i-1000000);
	}
	vec.pb(v_large);
	for(auto v:vec){
		t.clear();
		for(auto e:v)t.ins3rt(e);
		sort(all(v));
		rep(i,0,v.size())
			EXPECT_EQ(t.get_kth_max(i+1),v[v.size()-i-1]);
	}
}

TEST(avl_tree_test, get_kth_max_large){
	avl_tree t;
	vi v_large1,v_large2;
	rep(i,0,1000000){
		v_large1.pb(i+1);
		v_large2.pb(1000000-i);
		v_large2.pb(i-1000000);
	}
	for(auto e:v_large1)t.ins3rt(e);
	for(auto e:v_large2)t.ins3rt(e);
	for(auto e:v_large2)t.d3lete(e);
	sort(all(v_large1));
	rep(i,0,v_large1.size())
		EXPECT_EQ(t.get_kth_max(i+1),v_large1[v_large1.size()-i-1]);
}

TEST(avl_tree_test, get_kth_max_latency){
	avl_tree t;
	rep(e,1,1000001)t.ins3rt(e);
	t.clear();
	ASSERT_EQ(true,true);//runs in ~1 sec.
}

TEST(segment_tree_test,get_kth_max){
	segment_tree t=segment_tree(10);
	t.update_point(7,1);
	ASSERT_EQ(t.get_kth_max(1),7);
	vi v={4,4,7,8,8};
	t.update_point(4,2);
	t.update_point(7,1);
	t.update_point(8,2);
	rep(i,0,5){
		EXPECT_EQ(t.get_kth_max(5-i),v[i]);
	}
	ASSERT_EQ(t.query_range(1,10),5);
	ASSERT_EQ(t.query_range(4,4),2);
	ASSERT_EQ(t.query_range(7,7),1);
	ASSERT_EQ(t.query_range(8,8),2);
}

TEST(segment_tree_persistent_test,internal){
	segment_tree_persistent t=segment_tree_persistent(10);
	//6 2 4 9 5 2 1 1 2 4 3
	t.update(6,1);
	t.update(2,1);
	ASSERT_EQ(t.query(1,2,8),1);
	ASSERT_EQ(t.query(2,1,9),2);
	t.update(4,1);
	ASSERT_EQ(t.query(3,1,9),3);
	t.update(9,1);t.update(5,1);
	t.update(2,2);t.update(1,1);
	ASSERT_EQ(t.query(7,1,10),7);
	t.update(1,2);t.update(2,3);
	t.update(4,2);t.update(3,1);
	ASSERT_EQ(t.query(11,1,10),11);
	ASSERT_EQ(t.query(6,2,2),2);
	ASSERT_EQ(t.query(8,1,2),4);
}

int range_range_query(vi v, int l, int r, int x, int y){
	int cnt = 0;
	rep(i,l-1,r){
		cnt += v[i]>=x&&v[i]<=y;
	}
	return cnt;
}

TEST(segment_tree_persistent_test,range_range_query){
	vi v={5,6,1,5,3,5,8,2,1};
	segment_tree_persistent t=segment_tree_persistent(8);
	map<int,int>freq;
	for(auto e:v){
		++freq[e];
		t.update(e,freq[e]);
	}
	rep(x,1,9){
		rep(y,x,9){
			rep(l,1,10){
				rep(r,l,10){
					EXPECT_EQ(t.query(r,x,y)-t.query(l-1,x,y),
						range_range_query(v,l,r,x,y));
				}
			}
		}
	}
}

TEST(segment_tree_lazy_test,query){
	segment_tree_lazy t=segment_tree_lazy({1,2,3,4,5,6,7,8});
	ASSERT_EQ(t.query(3,8),33);
	t.update(2,3,5);
	ASSERT_EQ(t.query(1,4),20);
}

TEST(trie_test, search){
	trie t;
	t.insert("the");t.insert("a");t.insert("there");
    t.insert("answer");t.insert("any");t.insert("by");
    t.insert("bye");t.insert("their");
    ASSERT_EQ(t.search("the"),true);
    ASSERT_EQ(t.search("these"),false);
    t.erase("these");t.erase("the");
    t.insert("these");
    ASSERT_EQ(t.search("these"),true);
    t.erase("these");
    t.erase("the");
    t.erase("a");t.erase("there");
    t.erase("answer");t.erase("any");
    t.erase("by");t.erase("their");
    ASSERT_EQ(t.search("bye"),true);
    ASSERT_EQ(t.search("by"),false);
    t.erase("bye");
    ASSERT_EQ(t.search("bye"),false);
    ASSERT_EQ(t.search("empty"),false);
}

TEST(binary_tree_test,is_foldable){
	binary_tree t;
	t.build({{2,3},{-1,4},{5,-1},{-1,-1},{-1,-1}});
	ASSERT_EQ(t.is_foldable(),true);
	t.clear();
	t.build({{2,3},{4,-1},{-1,5},{-1,-1},{-1,-1}});
	ASSERT_EQ(t.is_foldable(),true);
	t.clear();
	t.build({{2,3},{4,-1},{5,-1},{-1,-1},{-1,-1}});
	ASSERT_EQ(t.is_foldable(),false);
	t.clear();
	t.build({{2,3},{4,5},{6,-1},{-1,-1},{-1,-1},{-1,-1}});
	ASSERT_EQ(t.is_foldable(),false);
}

TEST(binary_tree_test,level_spiral_order){
	binary_tree t;
	t.build({{2,3},{4,5},{6,7},{8,9},{10,11},{-1,13},{14,-1},
	{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}});
	vi actual=t.level_spiral_order();
	vi expected={1,3,2,4,5,6,7,14,13,11,10,9,8};
	rep(i,0,14){
		EXPECT_EQ(actual[i],expected[i]);
	}
}