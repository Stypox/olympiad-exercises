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

struct Mod {
	int V, D, cumD;
};

struct Shi {
	int i, cumD;
};

int32_t main() {
	int N,S,K;
	in>>N>>S>>K;

	vector<Mod> mods(N);
	int cumD=0;
	for(int n = 0; n < N-1; ++n) {
		mods[n].cumD=cumD;
		in>>mods[n].D;
		cumD+=mods[n].D;
	}
	mods.back().D = -1;
	mods.back().cumD = cumD;
	for(int n = 0; n < N; ++n)
		in>>mods[n].V;


	int left=0, right=0, totv=0, s=0;
	deque<int> shields;
	for(int s = 0; s != S; ++s) {
		int shiLeft = right;
		++right;
		while(right<N && mods[right].cumD-mods[shiLeft].cumD <= K) {
			totv+=mods[right].V;
			++right;
		}

		int shiPos=right-1;
		shields.push_back(shiPos);
		while(right<N && mods[right].cumD-mods[shiPos].cumD <= K) {
			totv+=mods[right].V;
			++right;
		}
	}

	while(1) {

	}
}
