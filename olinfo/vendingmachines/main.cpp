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
	int T;
	in>>T;

	for(int t=0;t<T;++t){
		int N,Q;
		in>>N>>Q;

		vector<int> P(N);
		for(int n=0;n<N;++n){
			in>>P[n];
		}

		int m=0;
		bool hacker=false;
		for(int q=0;q<Q;++q){
			int l;
			in>>l;
			if (l>=0){
				m+=l;
			} else {
				m-=P[-l-1];
			}
			if (m<0) hacker=true;
		}

		if (hacker) {
			out<<"HACKER\n";
		} else {
			out<<"OK\n";
		}
	}
}
