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

int main() {
	while(1){
		si N,M;
		in>>N>>M;
		if(!in) break;

		vec<vec<si>> data(1000002);
		for(int n = 1; n <= N; ++n) {
			si v;
			in>>v;
			data[v].push_back(n);
		}

		for(int m = 0; m != M; ++m) {
			si k,v;
			in>>k>>v;
			if(k>data[v].size()) {
				out<<0;
			} else {
				out<<data[v][k-1];
			}
			out<<"\n";
		}
	}
}
