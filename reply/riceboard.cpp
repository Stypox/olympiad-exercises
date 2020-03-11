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
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		deb("\n\n\n");
		int R, N, M;
		in>>R>>N>>M;

		N = N*N;

		int times = log2(N);
		vector<int> powerR(times+1); // R^1, R^2, R^4, R^8
		vector<int> vals(times+1);
		powerR[0]=R;
		vals[0]=1;

		for(int tim = 1; tim <= times; ++tim) {
			powerR[tim] = (powerR[tim-1] * powerR[tim-1]) % M;
			vals[tim] = (vals[tim-1] * (1+powerR[tim-1])) % M;
		}

		debc(powerR, "powerR  ");
		debc(vals,   "vals    ");

		int sum = 0;
		int base = 1;
		while(N>0){
			times = log2(N);
			sum += (vals[times] * base) % M;
			sum %= M;

			base *= powerR[times];
			base %= M;

			N -= (1LL<<times);
			deb(times, N);
		}

		//vector<int>{}[3245678] = 7;

		out << "Case #" << t+1 << ": " << sum << "\n";
	}
}