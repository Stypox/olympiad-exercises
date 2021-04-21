#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int long long

int compute(int n) {
	int sqrtint = sqrt(n);
	int res = 0;
	for(int i=1;i<=sqrtint;++i) {
		res += n / i;
	}
	return res*2 - sqrtint*sqrtint;
}