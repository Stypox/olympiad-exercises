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

struct Card{
	char seed,val;
	si x;
	Card(char s, char v):seed{s},val{v},x{(v=='A'||v=='K'||v=='Q'||v=='J') ? 10 : (v-'0')}{}
};

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		vec<Card> cards;
		for (size_t i = 0; i < 52; i++) {
			str s;
			in>>s;
			cards.emplace_back(s[1],s[0]);
		}
		
		si Y=0,i=52-25-1;
		for (size_t j = 0; j < 3; j++) {
			Y+=cards[i].x;
			i+=(cards[i].x-11);
		}
		
		deb(i,Y);
		si idx = (Y<=i ? Y : (Y-i-1+52-25-1));
		out<<"Case "<<t+1<<": "<<cards[idx].val<<cards[idx].seed<<"\n";
	}
}
