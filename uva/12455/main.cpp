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
		si N,P;
		in>>N>>P;

		vec<si> L(P);
		for(auto&& l : L)
			in>>l;
		
		bool found=false;
		for(si i=0; i!=(1<<P); ++i) {
			si sum=0;
			for(int p = 0; p != P; ++p) {
				if(i&(1<<p)) sum+=L[p];
			}

			if (sum==N) {
				found=true;
				break;
			}
		}

		out<<(found ? "YES\n" : "NO\n");
	}
}
