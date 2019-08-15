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
	si t=0;
	while (1) {
		str line;
		in>>line;
		if(line=="end") break;
		++t;

		array<si, 26> lastOccour;
		for(int i = 0; i != 26; ++i) {
			lastOccour[i] = line.find_last_of('A'+i);
		}

		vec<vec<ch>> stacks;
		for(int i = 0; i != line.size(); ++i) {
			auto&& c = line[i];

			bool put=false;
			for(auto it = stacks.begin(); it != stacks.end(); ++it) {
				auto&& s = *it;
				if(c<=s.back()){
					put=true;
					s.push_back(c);
					break;
				}
			}

			if(!put){
				stacks.push_back({});
				stacks.back().push_back(c);
			}

			sort(stacks.begin(), stacks.end(), [](const vec<ch>& a, const vec<ch>& b) { return a.back() < b.back(); });
		}

		#ifndef ONLINE_JUDGE
		for(auto&& s : stacks) {
			for(auto&& c : s) {
				cout<<c;
			}
			cout<<"\n";
		}
		cout<<"\n\n";
		#endif

		out<<"Case "<<t<<": "<<stacks.size()<<"\n";
	}
}
