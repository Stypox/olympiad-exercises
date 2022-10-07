#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

// poss. coppie: ss sd ds dd
// ss = 0
// ds = 0
// dd = 0
// sd ss = 0
// ds sd = 0
// dd sd = 0
// sd sd = sd

// ss dd sd dd sd sd ss ds ds ds ds ds dd ds ds ds ds sd

signed main() {
	int N;
	string S;
	in>>N>>S;

	assert(N%2 == 1);
	vector<bool> v(N/2 + 1, true);

	for(int n = 0; n != N; n += 2) {
		string piece = S.substr(n,2);
		if (piece == "SS") {

		} else if (piece == "SD") {

		} else if (piece == "DS") {

		} else if (piece == "DD") {

		}
	}
}
