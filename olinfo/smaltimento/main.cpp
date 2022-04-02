#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
void debprocs(const vector<Proc>& procs){
	for(int m=0;m<procs.size();++m){
		cout<<"proc "<<m<<"\n  from: "<<procs[m].from<<"\n  costTot: "<<procs[m].costTot<<"\n  to: ";
		deb(procs[m].to); cout<<"  usedTosCost: "; deb(procs[m].usedTosCost); cout<<"\n";
	}
}
#define unordered_set set
#define unordered_map map
#else
#define deb(...)
#define debprocs(...)
#endif

struct Proc{
	int from;
	unordered_map<int, int> to;
	unordered_map<int, ll> usedTosCost;
	ll costTot=1;
};

ll smaltisci(int N, int M, vector<int> A, vector<vector<int>> B) {
	vector<unordered_set<int>> neededBy(N);
	vector<Proc> procs(M);
	priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
	for(int m=0;m<M;++m){
		procs[m].from=A[m];
		for(int e:B[m]){
			procs[m].to[e]++;
			neededBy[e].insert(m);
		}
		if(B[m].size() == 0){
			pq.push({1,m});
		}
	}

	while(!pq.empty()){
		auto [cost,m] = pq.top();
		pq.pop();
		deb("cost",cost,"  m",m);

		int from=procs[m].from;
		if (from==0){
			deb("\n", neededBy, "\n");
			debprocs(procs);
			return cost;
		}

		for(auto e:neededBy[from]){
			if(procs[e].usedTosCost.count(from)){
				if (procs[e].usedTosCost[from] > cost) {
					procs[e].costTot += (cost-procs[e].usedTosCost[from])*procs[e].to[from];
					procs[e].usedTosCost[from] = cost;
				}
			} else {
				procs[e].costTot += cost*procs[e].to[from];
				procs[e].usedTosCost[from] = cost;

				if(procs[e].usedTosCost.size() == procs[e].to.size()){
					pq.push({procs[e].costTot, e});
				}
			}
		}
	}

	assert(false);
	return 0;
}
