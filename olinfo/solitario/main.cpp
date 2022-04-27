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

signed main() {
	int N,M;
	in>>N>>M;
	if (N>M) swap(N,M);

	vector<vector<bool>> v(N, vector<bool>(M, false));
	auto at = [&](int n, int m) {
		return (n < 0 || n >= N || m < 0 || m >= M) ? false : v[n][m];
	};

	int res=0;
	function<void(int, int, int)> rec = [&](int n, int m, int resHere) {
		if (resHere < (n*M+m)/2) {
			return;
		}
		n+=m/M;
		m%=M;
		if (n >= N) {
			res=max(res, resHere);
			return;
		}

		rec(n,m+1,resHere);
		if (!(at(n-1, m-1) && at(n-2, m-2))
				&& !(at(n-1, m) && at(n-2, m))
				&& !(at(n, m-1) && at(n, m-2))
				&& !(at(n-1, m+1) && at(n-2, m+2))) {
			v[n][m] = true;
			rec(n, m+1, resHere+1);
			v[n][m] = false;
		}
	};

	rec(0,0,0);
	out<<res<<endl;
}
