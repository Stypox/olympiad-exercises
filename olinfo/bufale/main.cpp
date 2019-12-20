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
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

long long solve(int N, int*M, int*P) {
	vec<pair<int, int>> cose;
	for(int n = 0; n != N; ++n) {
		cose.emplace_back(M[n] - P[n], n);
	}

	nth_element(cose.begin(), cose.begin() + N/2, cose.end());

	long long tot=0;
	for(int n = 0; n != N/2; ++n) {
		tot+=P[cose[n].second];
		tot+=M[cose[n + N/2].second];
	}
	return tot;
}
/*
int main() {
	int a[] {0,0,0,1,1,1,1,1};
	int b[] {1,1,1,1,1,1,0,0};
	cout<<solve(8, a, b)<<"\n";
}
*/