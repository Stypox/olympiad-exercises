#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<endl;}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

int quadri(int N, long long M, int V[]) {
	auto doable = [&](int m){
		long long s=accumulate(V, V+m, 0LL);
		if (s>M) return false;
		for(int i=0;i<N-m;++i) {
			s-=V[i];
			s+=V[i+m];
			if (s>M) return false;
		}
		return true;
	};

	int l=0, h=N+1;
	while((h-l) != 1) {
		int m=(l+h)/2;
		if (doable(m)) {
			l=m;
		} else {
			h=m;
		}
	}
	return l;
}
