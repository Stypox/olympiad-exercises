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

struct dt {
	si par=-1;
	si n=1;
};

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si F;
		in>>F;

		si i=0;
		map<str,si> idxs;
		auto getIdx = [&](str s) {
			if (!idxs.count(s)) {
				idxs[s]=i;
				++i;
			}
			return idxs[s];
		};

		vec<dt> friends;
		auto parent = [&](si a) {
			deb(a);
			if (a == friends.size()) {
				deb(a,friends.size());
				friends.resize(a+1);
				friends[a].par = a;
			} else {
				while(friends[a].par != a)
					a = friends[a].par;
			}
			return a;
		};
		auto connect = [&](si a, si b) {
			si pa=parent(a);
			si pb=parent(b);
			if (pa!=pb) {
				friends[pa].par = pb;
				friends[pb].n += friends[pa].n;
			}
			out<<friends[pb].n<<"\n";
		};

		for(int f = 0; f != F; ++f) {
			str a,b;
			in>>a>>b;
			si ia = getIdx(a);
			si ib = getIdx(b);
			connect(ia,ib);
		}
	}
}
