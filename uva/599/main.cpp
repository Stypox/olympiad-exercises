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
	in.ignore();

	array<si,26> letters;
	for(int t = 0; t != T; ++t) {
		fill(letters.begin(), letters.end(), -1);

		si E=0;
		str tmp;
		getline(in,tmp);
		while(tmp[0]!='*') {
			++E;
			letters[tmp[1]-'A']=1;
			letters[tmp[3]-'A']=1;
			getline(in,tmp);
		}

		getline(in,tmp);
		si V=(tmp.size()+1)/2;
		for(int v = 0; v != V; ++v) {
			si i=tmp[v*2]-'A';
			if (letters[i]==-1) letters[i]=0;
		}

		si acorns = count(letters.begin(), letters.end(), 0);
		si alltrees = V-E;
		si trees = alltrees-acorns;

		out<<"There are "<<trees<<" tree(s) and "<<acorns<<" acorn(s).\n";
	}
}
