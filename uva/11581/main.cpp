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
		array<bitset<3>, 3> bits;
		array<bitset<3>, 3> bits2;
		in>>bits[0]>>bits[1]>>bits[2];

		si count=0;
		while(1) {
			bool all0=true;
			for(auto&& line : bits) {
				all0 &= !(line[0] || line[1] || line[2]);
			}
			if (all0) break;

			bits2[0][0]=(bits[0][1]+bits[1][0])%2;
			bits2[0][2]=(bits[0][1]+bits[1][2])%2;
			bits2[2][0]=(bits[2][1]+bits[1][0])%2;
			bits2[2][2]=(bits[2][1]+bits[1][2])%2;

			bits2[1][0]=(bits[0][0]+bits[2][0]+bits[1][1])%2;
			bits2[0][1]=(bits[0][0]+bits[0][2]+bits[1][1])%2;
			bits2[1][2]=(bits[0][2]+bits[2][2]+bits[1][1])%2;
			bits2[2][1]=(bits[2][0]+bits[2][2]+bits[1][1])%2;

			bits2[1][1]=(bits[0][1]+bits[1][0]+bits[2][1]+bits[1][2])%2;

			bits = bits2;
			++count;
		}

		out<<count-1<<"\n";
	}
}
