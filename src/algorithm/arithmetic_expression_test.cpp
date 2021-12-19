#include "gtest/gtest.h"
#include "arithmetic_expression.cpp"

TEST(arithmetic_expression_test,infix_to_postfix){
	arithmetic_expression a;
	ASSERT_EQ(a.infix_to_postfix("a+b*c"),"abc*+");
	ASSERT_EQ(a.infix_to_postfix("a+b*(c^d-e)^(f+g*h)-i"),
		"abcd^e-fgh*+^*+i-");
}

TEST(arithmetic_expression_test,prefix_to_infix){
	arithmetic_expression a;
	ASSERT_EQ(a.prefix_to_infix("+a*bc"),"(a+(b*c))");
	ASSERT_EQ(a.prefix_to_infix("-+a*b^-^cde+f*ghi"),
		"((a+(b*(((c^d)-e)^(f+(g*h)))))-i)");
}

TEST(arithmetic_expression_test,prefix_to_postfix){
	arithmetic_expression a;
	ASSERT_EQ(a.prefix_to_postfix("+a*bc"),"abc*+");
	ASSERT_EQ(a.prefix_to_postfix("-+a*b^-^cde+f*ghi"),
		"abcd^e-fgh*+^*+i-");
}

TEST(arithmetic_expression_test,evaluate_postfix){
	arithmetic_expression a;
	ASSERT_EQ(a.evaluate_postfix("245*+"),22);
	ASSERT_EQ(a.evaluate_postfix("3324^6-23+-++"),11);
}

TEST(arithmetic_expression_test,evaluate_infix){
	arithmetic_expression a;
	ASSERT_EQ(a.evaluate_postfix(a.infix_to_postfix("2+4*5")),22);
	ASSERT_EQ(a.evaluate_postfix(
		a.infix_to_postfix("3+3+((2^4)-6)-(2+3)")),11);
}

TEST(arithmetic_expression_test,evaluate_prefix){
	arithmetic_expression a;
	ASSERT_EQ(a.evaluate_postfix(a.prefix_to_postfix("+*452")),22);
	ASSERT_EQ(a.evaluate_postfix(
		a.prefix_to_postfix("+3+3--^246+23")),11);

}