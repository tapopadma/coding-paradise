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

class arithmetic_expression{
	vector<char>operators={'^','*','/','%','+','-'};
	int operator_precedence(char ch){
		rep(i,0,operators.size()){
			if(operators[i]==ch)
				return operators.size()-i;
		}
		return 0;
	}
	bool is_operator(char ch){
		for(auto e:operators){
			if(e==ch)return true;
		}
		return false;
	}
	int calculate(int a, int b, char ch){
		if(ch=='+')return a+b;
		if(ch=='-')return a-b;
		if(ch=='*')return a*b;
		if(ch=='/')return a/b;
		if(ch=='^')return pow(a,b);
		return a+b;
	}
public:
	string prefix_to_postfix(string);
	string prefix_to_infix(string);
	string infix_to_postfix(string);
	int evaluate_postfix(string);
};

/** Compilers use postfix to evaluate arithmetic expression.*/
int arithmetic_expression::evaluate_postfix(string postfix){
	stack<string>s;
	rep(i,0,postfix.length()){
		char ch=postfix[i];
		if(is_operator(ch)){
			int b = stoi(s.top());s.pop();
			int a = stoi(s.top());s.pop();
			s.push(to_string(calculate(a,b,ch)));
		}else{
			string num;num+=ch;
			s.push(num);
		}
	}
	return stoi(s.top());
}

/** Infix: human readable arithmetic expression.
 * Prefix: operator will preceeded by operands.
 * Postfix: operator will be followed by operands.*/
string arithmetic_expression::infix_to_postfix(string infix){
	string postfix;
	stack<char>s;
	rep(i,0,infix.length()){
		char ch = infix[i];
		if(ch=='('){
			s.push(ch);
		} else if(ch==')'){
			while(!s.empty()&&s.top()!='('){
				postfix+=s.top();s.pop();
			}
			s.pop();
		} else if(is_operator(ch)){
			while(!s.empty()&&is_operator(s.top())
				&&operator_precedence(s.top())>=
				operator_precedence(ch)){
				postfix+=s.top();s.pop();
			}
			s.push(ch);
		} else{
			postfix += ch;
		}
	}
	while(!s.empty())postfix+=s.top(),s.pop();
	return postfix;
}

string arithmetic_expression::prefix_to_infix(string prefix){
	stack<string>s;
	for(int i=prefix.length()-1;i>=0;--i){
		char ch=prefix[i];
		if(is_operator(ch)){
			string str;str+='(';
			str+=s.top();s.pop();
			str+=ch;
			str+=s.top();s.pop();
			str+=')';
			s.push(str);
		}else{
			string str;str+=ch;
			s.push(str);
		}
	}
	return s.top();
}

string arithmetic_expression::prefix_to_postfix(string prefix){
	stack<string>s;
	for(int i=prefix.length()-1;i>=0;--i){
		char ch=prefix[i];
		if(is_operator(ch)){
			string str;str+=s.top();s.pop();
			str+=s.top();s.pop();
			str+=ch;
			s.push(str);
		}else{
			string str;str+=ch;
			s.push(str);
		}
	}
	return s.top();
}