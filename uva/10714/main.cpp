#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int L,N;
		in>>L>>N;

		int minus=-1,plus=-1;
		for(int n = 0; n != N; ++n) {
			int l;
			in>>l;

			if (max(l, L-l) > plus) {
				plus = max(l, L-l);
			}
			if (min(l, L-l) > minus) {
				minus = min(l, L-l);
			}
		}

		out<<minus<<" "<<plus<<"\n";
	}
}
