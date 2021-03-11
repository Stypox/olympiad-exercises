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

vector<int> getPoss(vector<string> strings, string val) {
	vector<int> poss;
	for (auto&& string : strings) {
		poss.push_back(string.find(val));
		if(poss.back() == std::string::npos)
			return {};
	}
	return poss;
}

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N = 4, M, unused;
		for(int n = 0; n != N; ++n)
			in >> unused;
		in >> M;

		vector<string> strings(N);
		for(int n = 0; n != N; ++n)
			in >> strings[n];

		vector<int> poss;
		for(int n = 0; n != strings[0].size()-M+1; ++n) {
			poss = getPoss(strings, strings[0].substr(n, M));

			if (poss.size() == N)
				break;
		}

		out << "Case #" << t+1 << ":";
		for (int pos : poss) out << " " << pos;
		out << "\n";
	}

	return 0;
}