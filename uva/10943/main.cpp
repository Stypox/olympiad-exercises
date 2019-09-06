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

si N,K;
vec<vec<si>> mem;

si rec(si n, si k) {
	if (n<0) return 0;
	if (k==0) return (n==0);
	if (mem[n][k-1] >= 0) return mem[n][k-1];

	si sum=0;
	for(si n2=0;n2<=N;++n2) {
		sum += rec(n-n2, k-1);
		sum %= 1000000;
	}

	mem[n][k-1] = sum;
	return sum;
}

int main() {
	while(1) {
		in>>N>>K;
		if (N==0 && K==0) break;

		mem = vec<vec<si>>(N+1, vec<si>(K, -1));
		si res = rec(N, K);
		out<<res<<"\n";
	}
}
