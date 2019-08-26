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

si M,C;
vec<vec<si>> items;
vec<vec<si>> mem;

si rec(si m, si c) {
	if (m<0) return -1;
	if (c==C) return m;
	if (mem[m][c] != numeric_limits<si>::min()) return mem[m][c];

	vec<si> next;
	for(auto&& price : items[c]) {
		si el = rec(m-price, c+1);
		if (el>=0)
			next.push_back(el);
	}
	
	if (next.empty()) {
		mem[m][c] = -1;
	} else {
		mem[m][c] = *min_element(next.begin(), next.end());
	}
	return mem[m][c];
}

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		in>>M>>C;

		items.resize(0);
		items.resize(C);
		for(auto&& item : items) {
			si N;
			in>>N;
			item.resize(N);
			for(auto&& price : item) {
				in>>price;
			}
		}

		mem = vec<vec<si>>(M+1, vec<si>(C, numeric_limits<si>::min()));
		si res = rec(M,0);
		if (res==-1) {
			out<<"no solution\n";
		} else {
			out<<M-res<<"\n";
		}
	}
}
