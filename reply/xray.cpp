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

int* calc (int* beg, int* const end, int& num) {
	while (beg != end && *beg == 0) ++beg;
	if (beg == end) return beg;
	int* last = beg;
	while (last != end && *last != 0) ++last;

	std::for_each(beg, last, [](int& v) { --v; });
	++num;
	return beg;
}

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N;
		in >> N;

		vector<int> vals;
		for(int n = 0; n != N; ++n) {
			int val;
			in >> val;
			vals.push_back(val);
		}

		int* beg = &vals[0];
		int* const end = beg + N;
		int num = 0;
		while (1) {
			beg = calc(beg, end, num);
			if (beg == end) break;
		}

		out << "Case #" << t+1 << ": " << num << "\n";
	}

	return 0;
}