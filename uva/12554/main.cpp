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
	si N;
	in >> N;

	vec<str> names(N);
	for(int n = 0; n != N; ++n) {
		in>>names[n];
	}

	constexpr array<const char*, 16> ws ={"Happy", "birthday", "to", "you", "Happy", "birthday", "to", "you", "Happy", "birthday", "to", "Rujia", "Happy", "birthday", "to", "you"};

	si times = N/ws.size() + (N!=ws.size());
	si in=0;
	for(int t = 0; t != times; ++t) {
		for(auto&& w : ws) {
			out<<names[in]<<": "<<w<<"\n";
			++in;
			if(in==names.size())in=0;
		}
	}
}
