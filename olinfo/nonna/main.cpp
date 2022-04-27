#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
template<class T>istream&operator>>(istream&i, vector<T>& v){for(auto& e:v){i>>e;}return i;}
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int N,K;
	in>>N>>K;

	vector<int> P(N);
	in>>P;

	vector<vector<bool>> mem(N, vector<bool>(K+1, false));
	int res=numeric_limits<int>::max();
	function<void(int,int)> rec = [&](int n, int k) {
		if (k<=0) {
			res=min(res,K-k);
			if (k==0) {
				out<<K<<endl;
				exit(0); // exit fast
			}
			return;
		}
		if (n>=N || mem[n][k]) return;

		mem[n][k]=true;
		rec(n+1, k);
		rec(n+1, k-P[n]);
	};

	rec(0,K);
	out<<res<<endl;
}
