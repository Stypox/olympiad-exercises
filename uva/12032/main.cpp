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
		int N;
		in>>N;

		vector<int> r(N);
		for(int n=0;n<N;++n){
			in>>r[n];
		}

		auto doable = [&](int k){
			int h=0;
			for(int n=0;n<N;++n){
				int diff=r[n]-h;
				if (diff > k) {
					return false;
				} else if (diff == k) {
					--k;
				}
				h+=diff;
			}
			return true;
		};

		int a=1,b=10000002;
		while(1){
			int m=(a+b-1)/2;
			if(doable(m)) {
				b=m+1;
			} else {
				a=m+1;
			}

			if (a==b-1) {
				break;
			}
		}

		out<<"Case "<<t+1<<": "<<a<<"\n";
	}
}
