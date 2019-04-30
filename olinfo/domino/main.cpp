#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

si resolve(si last, vec<pair<si,si>> cards) {
	si maxSoFar = 0;
	for(auto it = cards.begin(); it != cards.end(); ++it) {
		if (it->first==last) {
			auto cards2 = cards;
			cards2.erase(cards2.begin() + (it - cards.begin()));
			si val = resolve(it->second, cards2)+1;
			if (val > maxSoFar) maxSoFar = val;
		} else if (it->second==last) {
			auto cards2 = cards;
			cards2.erase(cards2.begin() + (it - cards.begin()));
			si val = resolve(it->first, cards2)+1;
			if (val > maxSoFar) maxSoFar = val;
		}
	}
	return maxSoFar;
}

int main() {
	si N;
	in>>N;
	vec<pair<si,si>> cards(N);
	for(int n = 0; n != N; ++n)
		in>>cards[n].first>>cards[n].second;
	
	si maxSoFar = 0;
	for(auto it = cards.begin(); it != cards.end(); ++it) {
		{
			auto cards2 = cards;
			cards2.erase(cards2.begin() + (it - cards.begin()));
			si val = resolve(it->second, cards2)+1;
			if (val > maxSoFar) maxSoFar = val;
		}
		{
			auto cards2 = cards;
			cards2.erase(cards2.begin() + (it - cards.begin()));
			si val = resolve(it->first, cards2)+1;
			if (val > maxSoFar) maxSoFar = val;
		}
	}

	out<<maxSoFar;
}