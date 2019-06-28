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
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#endif

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si N;
		in>>N;

		si maxC=-1;
		for(int n = 0; n != N; ++n) {
			si C;
			in>>C;
			if(C>maxC) maxC=C;
		}

		out<<"Case "<<t+1<<": "<<maxC<<"\n";
	}
}
