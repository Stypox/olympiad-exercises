#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double
#define MOD 1000000007

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	string s;
	in >> s;

	int result = 0;
	int currPow26 = 1;
	for(auto it = s.rbegin(); it != s.rend(); ++it) {
		result += (*it - 'a') * currPow26;
		result %= MOD;
		currPow26 *= 26;
		currPow26 %= MOD;
		result += currPow26;
		result %= MOD;
	}
	result += MOD - currPow26;
	result %= MOD;

	out << result;
}
