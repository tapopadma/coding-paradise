#include "modulo.cpp"
#include "gtest/gtest.h"

TEST(modulo_test,power_chain){
	modulo* m;
	ASSERT_EQ(m->power_chain(new ll[3]{2,2,2},3,998244353),16);
	ASSERT_EQ(m->power_chain(new ll[3]{15926535,14,3},3,998244353),109718301);
}

TEST(modulo_test,power_chain_general){
	modulo* m;
	ASSERT_EQ(m->power_chain_general(new ll[3]{2,2,2},3,998244353),16);
	ASSERT_EQ(m->power_chain_general(new ll[3]{15926535,14,3},3,998244353),109718301);
}