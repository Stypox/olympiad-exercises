#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll fastExp(ll c, ll e, ll m) {
	if (e==0) return 1;
	ll base = fastExp(c, e/2, m);
	return (((base * base) % m) * (e%2 ? c : 1)) % m;
}

void decifra(int N, int d, int L, int messaggio[], char plaintext[]) {
	for(int l=0;l<L;++l){
		ll v=fastExp(messaggio[l], d, N);
		assert(v>='a' && v<='z');
		plaintext[l]=(uint8_t)v;
	}
	plaintext[L]='\0';
}
