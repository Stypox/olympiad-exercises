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

#define H 1000
int N,K,a,b;
vector<int> tempi, cariche;
vector<vector<vector<int>>> mem; // [pos][tempo][carica]

int minTime(int pos, int tempo, int carica) {
	if (pos >= H*K) return 0;


	if (carica >= 0) {
		return min()
	}
}

int32_t main() {
	in>>N>>K>>a>>b;

	tempi.resize(H*K);
	cariche.resize(H*K);
	mem.resize(H*K, vector<vector<int>>(H, vector<int>(K, -1)));
	int t=1,c=1;
	for(int i = 0; i != H*K; ++i) {
		tempi[i] = t;
		cariche[i] = c;

		t*=a;
		t%=H;
		c*=b;
		c%=K;
	}


}
