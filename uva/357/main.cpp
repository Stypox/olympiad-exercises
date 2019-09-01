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

array<si,5> coins{1,5,10,25,50};
vec<vec<si>> mem(5);

si rec(si i, si cents) {
	if (cents<0 || i>=coins.size()) return 0;
	if (cents==0) return 1;
	if (mem[i][cents] >= 0) return mem[i][cents];

	mem[i][cents] = rec(i, cents - coins[i]) + rec(i+1, cents);
	return mem[i][cents];
}

int main() {
	while (1) {
		si N;
		in>>N;
		if(!in) break;

		for(auto&& v : mem) {
			v.resize(max(mem.size(), (size_t)N+1), -1);
		}
		si ways = rec(0, N);

		if (ways == 1) {
			out<<"There is only 1 way";
		} else {
			out<<"There are "<<ways<<" ways";
		}
		out<<" to produce "<<N<<" cents change.\n";
	}
}
