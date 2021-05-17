#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

#define STPARAM 0, stVals.dmax.size()/2, 1
#define assert(x)
#define at operator[]

struct SegmentTree {
	vector<int> dmax;
	SegmentTree(int N) {
		int s=1;
		while(s<N) s*=2;
		s*=2;
		dmax.resize(s, numeric_limits<int>::min());
	}

	void update(int x, int v, int a, int b, int i) {
		if (x<a || x>=b) return;
		if ((b-a)==1) {
			dmax[i]=v;
			return;
		}

		update(x, v, a, (a+b)/2, i*2);
		update(x, v, (a+b)/2, b, i*2+1);
		dmax[i]=max(dmax[i*2], dmax[i*2+1]);
	}

	int qmax(int x, int y, int a, int b, int i) {
		if (a>=y || b<=x) return numeric_limits<int>::min();
		if (a>=x && b<=y) return dmax[i];
		return max(qmax(x, y, a, (a+b)/2, i*2),
					  qmax(x, y, (a+b)/2, b, i*2+1));
	}

	int at(int x) {
		return dmax.at(dmax.size()/2 + x);
	}
};

SegmentTree stPrev{0}, stVals{0};
vector<set<int>> pos;

void modifica(int i, int v);

void inizio(int N, int, int sfere[]) {
	stPrev=SegmentTree(N);
	stVals=SegmentTree(N);
	pos.resize(N+1);

	for(int n=0;n<N;++n) {
		pos[0].insert(n);
		stPrev.update(n, n-1, STPARAM);
		stVals.update(n, 0, STPARAM);
	}

	for(int n=0;n<N;++n){
		modifica(n, sfere[n]);
	}
}

void modifica(int i, int v) {
	int old = stVals.at(i);
	deb(i, v, old);

	// update prev for the next value same as old
	auto oldit = pos[old].lower_bound(i);
	assert(oldit != pos[old].end());
	auto olditnext = oldit; olditnext++;
	if (olditnext != pos[old].end()) {
		int oldprev = -1;
		if (oldit != pos[old].begin()) {
			auto olditprev = oldit; olditprev--;
			oldprev = *olditprev;
		}
		deb("old", *olditnext, oldprev);
		stPrev.update(*olditnext, oldprev, STPARAM);
	}
	pos[old].erase(oldit);

	// update prev for the next value same as v
	auto newit = pos[v].lower_bound(i);
	assert(newit == pos[v].end() || *newit != i);
	if (newit != pos[v].end()) {
		stPrev.update(*newit, i, STPARAM);
	}

	// update prev at i
	int newprev = -1;
	if (newit != pos[v].begin()) {
		auto newitprev = newit; newitprev--;
		newprev = *newitprev;
	}
	deb("new", i, newprev);
	stPrev.update(i, newprev, STPARAM);
	pos[v].insert(i);

	// update vals
	stVals.update(i, v, STPARAM);
}

bool verifica(int l, int r) {
	r++;
	deb("verifica", pair{l, r}, stVals.qmax(l, r, STPARAM), stPrev.qmax(l, r, STPARAM));
	return stVals.qmax(l, r, STPARAM) == r-l
	    && stPrev.qmax(l, r, STPARAM) < l;
}
