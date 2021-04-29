#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A, class B> ostream& operator<<(ostream& o, const pair<A, B>& p) {cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) {cout<<"[";for(size_t i=0;i<v.size();++i){if(i!=0){cout<<", ";}cout<<v[i];}cout<<"]";return o;}
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

signed main() {
	
}
