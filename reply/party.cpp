#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N;
		in >> N;

		int sum = 0;
		for(int n = 0; n != N; ++n) {
			int val;
			in >> val;
			if (val > 0)
				sum += val;
		}

		out << "Case #" << t+1 << ": " << sum << "\n";
	}

	return 0;
}