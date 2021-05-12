#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int32_t
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

struct Event {
	int S=10001001, E=10001002, B=0, P=0, money=0;
	bool operator<(const Event& o) const {
		return S < o.S;
	}
	bool operator<(const int& o) const {
		return S < o;
	}
};

signed main() {
	int N,M;
	in>>N>>M;

	vector<Event> events(N+1);
	for(int n=0;n<N;++n){
		int D;
		in>>D>>events[n].S>>events[n].E>>events[n].B>>events[n].P;
		events[n].S += D*10000;
		events[n].E += D*10000;
	}

	sort(events.begin(), events.end());
	events[0].money=M;
	for(int n=0;n<N;++n){
		events[n+1].money=max(events[n].money, events[n+1].money);
		if(events[n].money >= events[n].B) {
			auto next=lower_bound(events.begin() + n, events.end(), events[n].E);
			next->money=max(next->money, events[n].money - events[n].B + events[n].P);
		}
	}

	out<<events[N].money;
}
