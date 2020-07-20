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
	int N;
	in>>N;

	vector<int> ladies;
	for(int n = 0; n != N; ++n) {
		int l;
		in>>l;
		ladies.push_back(l);
	}

	int Q;
	in>>Q;

	for(int q = 0; q != Q; ++q) {
		int h;
		in>>h;
		auto low = upper_bound(ladies.rbegin(), ladies.rend(), h, greater<int>());
		auto high = upper_bound(ladies.begin(), ladies.end(), h, less<int>());

		if (low == ladies.rend()) {
			out<<"X";
		} else {
			out<<*low;
		}
		out<<" ";

		if (high == ladies.end()) {
			out<<"X";
		} else {
			out<<*high;
		}
		out<<"\n";
	}
}
