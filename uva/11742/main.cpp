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

constexpr si fact(si n) {
	return (n==0) ? 1 : n*fact(n-1);
}

struct Con {
	si a,b,s;
	Con() : a{0},b{0},s{0} {}
};

int main() {
	while(1){
		si N,M;
		in>>N>>M;
		if(N==0 && M==0) break;

		vec<Con> constr(M);
		for(auto&& c : constr)
			in>>c.a>>c.b>>c.s;

		vec<si> teens(N);
		si i=0;
		generate(teens.begin(), teens.end(), [&i](){ return i++; });

		si all=0;
		si perms = fact(N);
		for(int p = 0; p != perms; ++p) {
			bool valid=true;
			for(auto&& c : constr) {
				if(c.s>0) {
					if(abs(teens[c.a]-teens[c.b]) > c.s) {
						valid=false;
						break;
					}
				} else {
					if(abs(teens[c.a]-teens[c.b]) < -c.s) {
						valid=false;
						break;
					}
				}
			}
			
			all+=valid;
			next_permutation(teens.begin(), teens.end());
		}

		out<<all<<"\n";
	}
}
