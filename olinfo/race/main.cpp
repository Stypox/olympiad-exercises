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
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

template<class T>
void print(T beg, T end) {
	while(beg!=end) {
		cout<<get<0>(*beg)<<":"<<get<1>(*beg)<<":"<<get<2>(*beg)<<" ";
		++beg;
	}
	cout<<"\n";
}

int main() {
	si N;
	in>>N;

	vec<tuple<si, si, si>> pos(N);
	for(si n = 0; n != N; ++n) {
		in>>get<0>(pos[n])>>get<2>(pos[n]);
		get<0>(pos[n]) += get<2>(pos[n]);
		get<1>(pos[n]) = n;
	}
	//print(pos.begin(), pos.end());

	si n=N;
	si beg=0;
	while(n!=1) {
		n/=2;
		nth_element(pos.begin()+beg, pos.begin()+beg+n, pos.end());
		//print(pos.begin() + beg, pos.end());
		beg+=n;

		//cout<<"\n";
		for (si a=beg; a!=pos.size(); ++a) {
			get<0>(pos[a]) += get<2>(pos[a]);
		}
		//print(pos.begin() + beg, pos.end());
	}

	out<<get<1>(pos[beg]);
}
