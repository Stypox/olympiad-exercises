#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

ll riciclo(int N, int M, vector<int> T, vector<int> P) {
	sort(T.begin(), T.end());
	P.resize(31, 0);
	vector<ll> needed(31, 0);

	for(auto t:T){
		for(int m=30;m>=0;m--){
			ll w=(1LL<<m);
			if(t>=w){
				t-=w;
				needed[m]++;
			}
		}
	}

	ll res=0;
	vector<ll> leftover(31, 0);
	for(int m=0;m<31;++m){
		ll totalNeededWeight = needed[m] * (1LL<<m);
		for(int x=0;x<m;++x){
			ll totalLeftoverWeight = leftover[x] * (1LL<<x);
			if (totalNeededWeight > totalLeftoverWeight) {
				res+=leftover[x];
				leftover[x]=0;
				totalNeededWeight-=totalLeftoverWeight;
			} else {
				ll countToRemove=totalNeededWeight/(1LL<<x);
				res+=countToRemove;
				leftover[x]-=countToRemove;
				totalNeededWeight-=countToRemove*(1LL<<x);
			}
			totalNeededWeight -= totalNeededWeight & (1LL<<x);
		}
		assert(totalNeededWeight % (1LL<<m) == 0);
		needed[m] = totalNeededWeight / (1LL<<m);

		if (P[m] <= needed[m]) {
			res+=P[m];
			leftover[m]=0;
		} else {
			res+=needed[m];
			leftover[m]=P[m]-needed[m];
		}
	}

	return res;
}
