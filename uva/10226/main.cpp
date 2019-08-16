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
	in.ignore(); in.ignore();

	out<<fixed<<setprecision(4);
	for(int t = 0; t != T; ++t) {
		if(t!=0) out<<"\n";
		si n=0;

		map<str,si> vals;
		while(1) {
			str s;
			getline(in, s);
			if(s.empty()) break;

			++n;
			++vals[s];
		}

		for(auto&& v: vals) {
			//cout<<v.first<<" "<<v.second<<"\n";
			out<<v.first<<" "<<(double)v.second/n*100<<"\n";
		}
	}
}
