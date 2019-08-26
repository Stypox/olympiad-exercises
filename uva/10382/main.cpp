#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

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

using Sprink = pair<flt,flt>;

int main() {
	while(1) {
		si N,L,W;
		in>>N>>L>>W;
		if(!in) break;

		vec<Sprink> sps;
		for(si n=0; n<N; ++n) {
			si pos, r;
			in>>pos>>r;

			if (r>(flt)W/2) {
				flt range = sqrt(r*r - (flt)W/2*(flt)W/2);
				sps.emplace_back(pos-range, pos+range);
			}
		}

		sort(sps.begin(), sps.end());
		si sprinkles=0;
		for(auto&& sp : sps) {
			deb(sp.first, sp.second);
		}

		si lasti = -1;
		while(1) {
			flt limit=(lasti>=0 ? sps[lasti].second : 0);
			if (limit >= L) break;

			si i=lasti+1;
			flt bestlimit=limit;
			while(1) {
				if(i>=sps.size() || sps[i].first > limit) break;
				if(sps[i].second > bestlimit) {
					lasti = i;
					bestlimit = sps[i].second;
				}
				++i;
			}

			if (bestlimit==limit) {
				sprinkles=-1;
				break;
			}
			++sprinkles;
		}

		out<<sprinkles<<"\n";
	}
}
