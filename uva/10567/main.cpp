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

si toInt(ch c) {
	if ('A' <= c && c <= 'Z')
		return c-'A';
	else
		return c-'a'+26;
}

int main() {
	while(1) {
		str S; si Q;
		in>>S>>Q;
		if(!in) break;
		in.ignore();
		
		array<vec<si>, 52> letters;
		for(si i = 0; i != S.size(); ++i)
			letters[toInt(S[i])].push_back(i);
		auto findFirstAtLeast = [&](si c, si i) {
			si a=0, b=letters[c].size(), lastSuitable=-1;

			while(1) {
				si med = (a+b)/2;
				if (letters[c][med] >= i) {
					lastSuitable=letters[c][med];
					b=med-1;
				} else {
					a=med+1;
				}
				if(a>b) break;
			}

			return lastSuitable;
		};
		
		for(int q = 0; q != Q; ++q) {
			str SS;
			in>>SS;

			si first=-1;
			si i=-1;
			for(auto&& c : SS) {
				i=findFirstAtLeast(toInt(c), i+1);
				if (i==-1) break;
				if (first==-1) first=i;
			}

			if (i==-1) {
				out<<"Not matched\n";
			} else {
				out<<"Matched "<<first<<" "<<i<<"\n";
			}
		}
	}
}
