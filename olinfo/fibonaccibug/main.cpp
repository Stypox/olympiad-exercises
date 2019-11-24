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

constexpr si fibn = 26;

vec<si> mem(100001);
constexpr array<si, fibn> grades {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393};
vec<pair<si, si>> offers;

si knapsack(si maxbugs) {
	if (maxbugs <= 0) return 0;
	if (mem[maxbugs] != -1) return mem[maxbugs];

	si maxSoFar = 0;
	for (const auto& [bugs, money] : offers) {
		if (maxbugs - bugs >= 0)
			maxSoFar = max(maxSoFar, money + knapsack(maxbugs - bugs));
	}

	mem[maxbugs] = maxSoFar;
	return maxSoFar;
}

int main() {
	int T;
	in>>T;
	
	for(int t = 0; t != T; ++t) {
		int N, K;
		in>>N>>K;

		offers.clear();
		for(int n = 0; n != N; ++n) {
			si A, B;
			in>>A>>B;
			if (A<fibn) offers.push_back({grades[A], B});
		}

		fill(mem.begin(), mem.end(), -1);
		out<<knapsack(K)<<"\n";
		debc(vector<si>(mem.begin(), mem.begin()+12));
	}
}
