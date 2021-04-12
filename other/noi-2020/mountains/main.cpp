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

	vector<pair<int, int>> mounts;
	for(int n = 0; n != N; ++n) {
		int H;
		in>>H;
		mounts.emplace_back(H,n);
	}
	sort(mounts.begin(), mounts.end());
	//for(auto m:mounts) cerr<<m.first<<","<<m.second<<" "; cerr<<"\n";


	int tot=0;
	set<pair<int,int>> seenSoFar;
	for(int n = 0; n < N;) {
		int height=mounts[n].first;

		int i = n+1;
		while(i < N && mounts[i].first==height) {
			++i;
		}

		for(int j = n; j != i; ++j) {
			int left = distance(seenSoFar.begin(), seenSoFar.upper_bound({mounts[j].second, mounts[j].first}));
			int right = seenSoFar.size() - left;

			//cerr<<height<<","<<index<<" -> "<<left<<"-"<<right<<"\n";
			tot+=left*right;
		}

		for(int j = n; j != i; ++j) {
			seenSoFar.emplace(mounts[j].second, mounts[j].first);
		}
		n=i;
	}

	out<<tot<<"\n";
}
