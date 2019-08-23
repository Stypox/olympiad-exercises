#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;
using El = pair<si, vec<si>>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

si N,R,M;
vec<El> towers;
vec<El> common;

si bestSum;
si bestTurnedOn;

void cel(si turnedOn) {
	deb("cel", turnedOn); cout.flush();
	assert(__builtin_popcountll(turnedOn) == R);
	vec<bool> used(common.size(), false);

	si sum=0;
	for(int n = 0; n != N; ++n) {
		if(turnedOn & (1<<n)) {
			sum += towers[n].first;
			for(auto&& com : towers[n].second) {
				if (used[com]) {
					sum -= common[com].first;
				} else {
					used[com]=true;
				}
			}
		}
	}

	if(sum>bestSum) {
		bestSum=sum;
		bestTurnedOn=turnedOn;
	}
}

void gen(si turnedOn, si min, si max) {
	deb("gen", turnedOn, min, max);
	if (max==N) {
		for (si a=min; a!=max; ++a) {
			cel(turnedOn+(1<<a));
		}
	} else {
		for (si a=min; a!=max; ++a) {
			gen(turnedOn+(1<<a), a+1, max+1);
		}
	}
}

int main() {
	si casnum=0;
	while(1) {
		in>>N>>R;
		deb("NR", N, R);
		if(N==0) break;

		towers.resize(0);
		towers.resize(N);
		for(auto&& t : towers)
			in>>t.first;
			
		in>>M;
		deb("M", M);
		common.resize(0);
		common.resize(M);
		for(int m = 0; m != M; ++m) {
			si T;
			in>>T;
			common[m].second.resize(T);
			
			for(int t = 0; t != T; ++t) {
				in>>common[m].second[t];
				--common[m].second[t];
				towers[common[m].second[t]].second.push_back(m);
			}
			in>>common[m].first;
		}
		
		bestSum=-1;
		gen(0, 0, N-R+1);

		++casnum;
		out<<"Case Number  "<<casnum<<"\n";
		out<<"Number of Customers: "<<bestSum<<"\n";
		out<<"Locations recommended:";
		for(int n = 0; n != N; ++n)
			if(bestTurnedOn & (1<<n))
				out<<" "<<n+1;
		out<<"\n\n";

		deb("NR", N, R, "END\n");
	}
}
