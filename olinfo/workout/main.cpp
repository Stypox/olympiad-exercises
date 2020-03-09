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

int N;
set<int> fat;

bool doable(int constraint) {
	set<int> fatDup{fat};
	
	int currsum = 0;
	while(!fatDup.empty()) {
		// trova il primo <= (constraint-currsum)
		auto it = fatDup.upper_bound(constraint - currsum);
		if (it == fatDup.begin()) {
			return false;
		}

		--it;
		currsum += *it;
		currsum = max(currsum, (int)0);
		deb(*it, currsum);
		fatDup.erase(it);
	}
	return true;
}

int32_t main() {
	in>>N;
	for(int n = 0; n != N; ++n) {
		int F;
		in>>F;
		fat.insert(F);
	}

	debc(fat);
	deb(doable(22));	
}
