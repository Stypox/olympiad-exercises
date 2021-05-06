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

#define int long long
#define DEF_TO 10000000

struct Interval {
	signed from, to;
	int value;

	Interval(int v = 0) : from{-1}, to{DEF_TO}, value{v} {}

	void mergeWith(const Interval& other) {
		from = max(from, other.from);
		to = min(to, other.to);
		value += other.value;
	}

	void addValue(const Interval& other) {
		value += other.value;
	}

	bool contains(signed day) {
		return day >= from && day < to;
	}
};
ostream&operator<<(ostream&o,const Interval&p){cout<<"["<<p.from<<", "<<p.to<<")"<<p.value;return o;}


struct Node {
	signed par=-1;
	vector<signed> chi;
	signed day=1000000;
	int juice=0;

	map<signed, Interval> savedNotTaken;
	Interval savedTaken;
	bool savedTakenCalculated=false;

	pair<bool, Interval> findSavedNotTaken(int maxd) {
		auto it = savedNotTaken.lower_bound(maxd);
		if (it != savedNotTaken.end() && it->second.contains(maxd)) {
			return {true, it->second};
		}
		if (it != savedNotTaken.begin() && prev(it)->second.contains(maxd)) {
			return {true, prev(it)->second};
		}
		return {false, {}};
	}
};

long long harvest(signed N, signed M, signed K, vector<signed>& P, vector<signed>& V, vector<signed>& D, vector<signed>& W) {
	vector<Node> nodes(N);
	for(int n=1;n<N;++n){
		nodes[n].par=P[n];
		nodes[P[n]].chi.push_back(n);
	}
	for(int n=0;n<N;++n){
		deb(n, nodes[n].par, nodes[n].chi);
	}

	for(int m=0;m<M;++m){
		nodes[V[m]].day = D[m];
		nodes[V[m]].juice = W[m];
	}

	function<Interval(signed, signed)> rec = [&](signed i, signed maxd) -> Interval {
		deb(i, maxd);

		auto [foundSavedNotTaken, savedNotTaken] = nodes[i].findSavedNotTaken(maxd);
		if (!foundSavedNotTaken) {
			if (nodes[i].savedNotTaken.count(maxd) != 0) {
				deb(nodes[i].savedNotTaken);
				assert(nodes[i].savedNotTaken.count(maxd) == 0);
			}
			for(auto c:nodes[i].chi){
				nodes[i].savedNotTaken[maxd].mergeWith(rec(c, maxd));
			}
			nodes[i].savedNotTaken[maxd].to = maxd+1;
			savedNotTaken = nodes[i].savedNotTaken[maxd];
		}
		if (nodes[i].juice == 0 || nodes[i].day > maxd) {
			deb(i, maxd, savedNotTaken, nodes[i].juice);
			return savedNotTaken;
		}

		deb(i, maxd, "savedTaken");
		if (!nodes[i].savedTakenCalculated) {
			nodes[i].savedTaken = Interval(nodes[i].juice);
			for(auto c:nodes[i].chi){
				nodes[i].savedTaken.addValue(rec(c, nodes[i].day));
			}
			nodes[i].savedTaken.from = nodes[i].day;
			nodes[i].savedTaken.to = DEF_TO;
			nodes[i].savedTakenCalculated = true;
		}

		deb(i, maxd, savedNotTaken, nodes[i].savedTaken);
		assert(savedNotTaken.contains(maxd));
		assert(nodes[i].savedTaken.contains(maxd));
		return savedNotTaken.value > nodes[i].savedTaken.value ? savedNotTaken : nodes[i].savedTaken;
	};

	/*for(int i=1;i<K+1;++i){
		deb(i, rec(1, i));
	}*/
	//deb(rec(1, 3));
	return rec(0, K+1).value;
}
