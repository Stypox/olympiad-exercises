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
	while(1) {
		si N;
		in>>N;
		if (!in || N<0 || N>3000) break;

		si last;
		in>>last;

		vector<bool> vals(N-1, false);
		for(int n = 0; n != N-1; ++n) {
			si curr;
			in>>curr;

			si diff = abs(last-curr)-1;
			if (diff >= 0 && diff < N-1) {
				vals[diff]=true;
			}

			last=curr;
		}

		bool foundAll=true;
		for(auto&& v : vals) {
			foundAll&=v;
		}
		if (foundAll) {
			out<<"Jolly\n";
		} else {
			out<<"Not jolly\n";
		}
	}
}
