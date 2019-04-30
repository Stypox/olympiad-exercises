#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

int ContaOperazioni(int N, int K, int* secchi) {
	si totalAbove = 0, totalBelow = 0;
	for(int n = 0; n != N; ++n) {
		if (secchi[n]-K >= 0) totalAbove+=secchi[n]-K;
		else totalBelow+=K-secchi[n];
	}
	return min(totalAbove, totalBelow) + abs(totalAbove-totalBelow);
}

// remove the main() function on submission
int main() {
	si N, K;
	in>>N>>K;
	int* secchi = new int[N];
	for(int n = 0; n != N; ++n)
		in>>secchi[n];
	
	out<<ContaOperazioni(N, K, secchi);
}