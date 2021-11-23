#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

class modulo{
	ll powx(ll,ll,ll);
	ll power_chain(ll*,int,int,ll);
	ll power_chain_general(ll*,int,int,ll);
	ll phi(ll);
public:
	ll power_chain(ll*,int,ll);
	ll power_chain_general(ll*,int,ll);
};

ll modulo::powx(ll x, ll n, ll mod){
	x%=mod;
	if(x==0)return 0;
	if(n==0)return 1;
	return (n&1)?(x*powx(x,n-1,mod))%mod:powx((x*x)%mod,n/2ll,mod);
}

ll modulo::power_chain(ll* a, int n, int i, ll mod){
	if(i+1==n)return a[i];
	return powx(a[i],power_chain(a,n,i+1,mod-1),mod);
}

/**
 * find (a0^a1^a2^...a^n-1)%mod if mod is prime.
 * 
 * Note: Fermat's little theorem => for a given prime p and a positive number a
 * (a^p - a) = 0 mod p => if gcd(a,p)=1, (a^(p-1) - 1) = 0 mod p =>
 * for any x(>0), a^x % p = a^(x%(p-1)) % p because if x=k*(p-1)+r then
 * (a^x)%p=(a^(k*(p-1)) * a^r)%p= 1 * (a^r)%p=(a^r)%p.
 */ 
ll modulo::power_chain(ll* a,int n, ll mod){
	return power_chain(a,n,0,mod);
}

/** totient function : no of i<n such that gcd(i,n)=1.*/
ll modulo::phi(ll n) {
	ll ret = n;
	for(ll p=2;p*p<=n;++p){
		if(n%p)continue;
		while(n%p==0)n/=p;
		ret=(ret-ret/p);
	}
	if(n>1)ret=(ret-ret/n);
	return ret;
}

ll modulo::power_chain_general(ll* a, int n, int i, ll mod){
	if(i+1==n)return a[i];
	return powx(a[i],power_chain_general(a,n,i+1,phi(mod)),mod);
}

/**
 * find (a0^a1^a2^...a^n-1)%mod if gcd(ai,phi(phi(phi(...n))))=1.
 * 
 * Note: Euler's totient theorem (general version of Fermat)=>
 * if gcd(a,n)=1, a^phi(n) - 1 = mod n where phi(n)=n(1-1/p1)(1-1/p2).. aka
 * number of i<n such that gcd(i,n)=1. This implies
 * a^x % n = a^(x%phi(n)) % n
 */
ll modulo::power_chain_general(ll* a, int n, ll mod){
	return power_chain_general(a,n,0,mod);
}