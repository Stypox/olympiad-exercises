//#pragma GCC optimize ("O3")
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

int f(int x) {
	return (x*(x+1))/2;
}

int lenA(int n) {
	int res = f(n);
	for (int o : {9, 99, 999, 9999}) {
		if (n > o) {
			res += f(n-o);
		}
	}
	return res;
}

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int i;
		in>>i;
		
		int low = 0, hi = (int)1<<(int)31;
		while(1) {
			int mid = (low+hi)/2;
			int res = lenA(mid);
			if (res >= i) {
				hi = mid;
			} else {
				if (low == mid) break;
				low = mid;
			}
		}

		i-=lenA(low);
		deb(low, hi, " -> ", lenA(low), lenA(hi));
		
		stringstream s;
		for (int k=1;k<=hi;++k){
			s<<k;
		}
		out<<s.str()[i-1]<<"\n";
	}
}
