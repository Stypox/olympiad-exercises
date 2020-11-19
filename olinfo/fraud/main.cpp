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
	int N;
	in>>N;

	vector<int> v(N);
	for (int n=0;n<N;++n){
		in>>v[n];
	}

	function<int(int, int)> rec = [&](int from, int to) -> int {
		if (from >= to) {
			return 0;
		}

		map<int, int> freq;
		for (int i=from;i<to;++i){
			freq[v[i]]++;
		}

		int mi=numeric_limits<int>::max(), ma=numeric_limits<int>::min();
		for (pair<int, int> el : freq) {
			mi=min(mi, el.second);
			ma=max(ma, el.second);
		}

		int res = mi*ma;
		int last = from;
		for (int i = from; i < to; ++i) {
			if(freq[v[i]]==mi) {
				res=max(res, rec(last, i));
				last=i+1;
			}
		}

		res=max(res, rec(last, to));
		return res;
	};

	out<<rec(0, N)<<"\n";
}
