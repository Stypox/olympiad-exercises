#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

si N, V;
vec<si> coins;
vec<vec<si>> mem;

si rec(si n, si v) {
	if (n==N) return abs(v - (V-v));
	if (mem[n][v] >= 0) return mem[n][v];

	mem[n][v] = min(rec(n+1, v+coins[n]), rec(n+1, v));
	return mem[n][v];
}

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		in>>N;

		V=0;
		coins.resize(N);
		for(auto&& coin : coins) {
			in>>coin;
			V+=coin;
		}

		mem.resize(0);
		mem.resize(N, vec<si>(N*501, -1));
		out<<rec(0, 0)<<"\n";
	}
}
