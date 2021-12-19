#include "gtest/gtest.h"
#include "strings.cpp"

void assert_vectors(vi actual, vi expected) {
	ASSERT_EQ(actual.size(),expected.size());
	rep(i,0,actual.size()){
		EXPECT_EQ(actual[i],expected[i]);
	}
}

TEST(kmp_test,find){
	kmp* km=new kmp("ABABDABACDABABCABAB","ABABCABAB");
	assert_vectors(km->find(),{10});
	km=new kmp("ABABABCABABABCABABABC","ABABAC");
	assert_vectors(km->find(),{});
	km=new kmp("princeandprincessprices","pri");
	assert_vectors(km->find(),{0,9,17});
}

TEST(z_test,find){
	z* zz=new z("ABABDABACDABABCABAB","ABABCABAB");
	assert_vectors(zz->find(),{10});
	zz=new z("ABABABCABABABCABABABC","ABABAC");
	assert_vectors(zz->find(),{});
	zz=new z("princeandprincessprices","pri");
	assert_vectors(zz->find(),{0,9,17});
}

TEST(suffix_array_test,build){
	suffix_array* s=new suffix_array("banana");
	assert_vectors(s->build(),{5,3,1,0,4,2});
}