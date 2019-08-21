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
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si A,B,C;
		in>>A>>B>>C;

		for(si x=-100; x<=100; ++x)
		for(si y=-100; y<=100; ++y)
		for(si z=-100; z<=100; ++z) {
			if ((x!=y && x!=z && y!=z) &&
					(x+y+z==A && x*y*z==B && x*x+y*y+z*z==C)) {
				out<<x<<" "<<y<<" "<<z<<"\n";
				goto end;
			}
		}
		out<<"No solution.\n";
		end: {}
	}
}
