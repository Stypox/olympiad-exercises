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

#define BINARY_LIFTING_SIZE 17

struct Node{
	int brig;
	vector<int> chi;
	array<int, BINARY_LIFTING_SIZE> par;
	array<int, BINARY_LIFTING_SIZE> val;
	int h=0;
};

void solve(int N, int Q, int* briganti, int* A, int* B, int* start, int* end, int* sol) {
	vector<vector<int>> adj(N);
	for(int n=0;n<N-1;++n){
		adj[A[n]].push_back(B[n]);
		adj[B[n]].push_back(A[n]);
	}

	vector<Node> nodes(N);
	for(int n=0;n<N;++n){
		nodes[n].brig=briganti[n];
	}

	function<void(int, int)> prop = [&](int i, int p) {
		nodes[i].par[0] = p;
		nodes[i].val[0] = max(nodes[i].brig, nodes[p].brig);
		nodes[i].h = nodes[p].h + 1;

		for(auto c:adj[i]){
			if(nodes[c].chi.empty()) {
				nodes[i].chi.push_back(c);
				prop(c, i);
			}
		}
	};
	prop(0,0);

	for(int e=1; e<BINARY_LIFTING_SIZE; ++e) {
		for(int n=0;n<N;++n){
			nodes[n].par[e] = nodes[nodes[n].par[e-1]].par[e-1];
			nodes[n].val[e] = max(nodes[n].val[e-1], nodes[nodes[n].par[e-1]].val[e-1]);
		}
	}

	for(int n=0;n<N;++n) deb(n, nodes[n].chi, nodes[n].h, nodes[n].par, nodes[n].val);


	auto lift = [&](int i, int h) {
		for(int e=0; e<BINARY_LIFTING_SIZE; ++e) {
			if(h & (1LL<<e)) {
				i = nodes[i].par[e];
			}
		}
		return i;
	};

	auto val = [&](int i, int h) {
		int res=0;
		for(int e=0; e<BINARY_LIFTING_SIZE; ++e) {
			if(h & (1LL<<e)) {
				res = max(res, nodes[i].val[e]);
				i = nodes[i].par[e];
			}
		}
		return res;
	};

	auto lca = [&](int u, int v) {
		int hu = nodes[u].h, hv = nodes[v].h;
		if (hu > hv) {
			u = lift(u, hu-hv);
		} else if (hv > hu) {
			v = lift(v, hv-hu);
		}
		assert(nodes[u].h == nodes[v].h);
		if (u == v) {
			return u;
		}

		for(int e=BINARY_LIFTING_SIZE-1; e>=0; --e) {
			if (nodes[u].par[e] != nodes[v].par[e]) {
				u = nodes[u].par[e];
				v = nodes[v].par[e];
			}
		}

		assert(nodes[u].par[0] == nodes[v].par[0]);
		return nodes[u].par[0];
	};


	for (int q=0;q<Q;++q){
		int anc = lca(start[q], end[q]);
		sol[q] = max(val(start[q], nodes[start[q]].h - nodes[anc].h),
		             val(end[q],   nodes[end[q]].h   - nodes[anc].h));
	}
}
