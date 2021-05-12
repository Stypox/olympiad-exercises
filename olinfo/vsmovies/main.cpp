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
void deb(){cout<<endl;}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

#define BINARY_LIFTING_SIZE 20

struct Edge {
	int a, b, w;
};
ostream& operator<<(ostream& o, const Edge& e) { o<<"("<<e.a<<" "<<e.b<<" "<<e.w<<")"; return o;}

struct UnionFindNode {
	int par=-1;
	int rank=0;
};
ostream& operator<<(ostream& o, const UnionFindNode& n) { o<<"|"<<n.par<<" "<<n.rank<<"|"; return o;}

struct Node {
	int h=-1;
	array<int, BINARY_LIFTING_SIZE> par;
	array<int, BINARY_LIFTING_SIZE> maxw;
};

signed main() {
	int N, S;
	in>>N>>S;
	vector<Edge> edges(N);
	for(int n=0;n<N;++n){
		in>>edges[n].a>>edges[n].b>>edges[n].w;
	}


	vector<UnionFindNode> ufnodes(S);
	function<int(int)> root = [&](int i) {
		if (ufnodes[i].par == -1) return i;
		return root(ufnodes[i].par);
	};
	auto merge = [&](int u, int v) {
		int ru = root(u), rv = root(v);
		if (ru==rv) return false;
		if (ufnodes[ru].rank > ufnodes[rv].rank) swap(ru, rv);

		ufnodes[rv].rank = max(ufnodes[rv].rank, ufnodes[ru].rank + 1);
		ufnodes[ru].par = rv;
		return true;
	};

	int mstWeight = 0;
	vector<vector<pair<int, int>>> mstEdges(S);
	vector<Edge> sortedEdges = edges;
	sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
	for(auto& edge : sortedEdges){
		deb(edge, ufnodes);
		if (merge(edge.a, edge.b)) {
			mstEdges[edge.a].push_back({edge.b, edge.w});
			mstEdges[edge.b].push_back({edge.a, edge.w});
			mstWeight += edge.w;
		}
	}
	deb(mstEdges);


	vector<Node> nodes(S);
	function<void(int, int, int)> dfs = [&](int i, int p, int w) {
		if (nodes[i].h != -1) return;
		nodes[i].h = nodes[p].h + 1;
		nodes[i].par[0] = p;
		nodes[i].maxw[0] = w;

		for(auto [to, w] : mstEdges[i]) {
			dfs(to, i, w);
		}
	};
	dfs(0, 0, 0);


	for(int e=1;e<BINARY_LIFTING_SIZE;++e){
		for(int s=0;s<S;++s){
			nodes[s].par[e] = nodes[nodes[s].par[e-1]].par[e-1];
			nodes[s].maxw[e] = max(nodes[s].maxw[e-1], nodes[nodes[s].par[e-1]].maxw[e-1]);
		}
	}

	auto lift = [&](int i, int h) {
		for(int e=0;e<BINARY_LIFTING_SIZE;++e){
			if(h & (1LL << e)) {
				i = nodes[i].par[e];
			}
		}
		return i;
	};
	auto maxw = [&](int i, int h) {
		int res=0;
		for(int e=0;e<BINARY_LIFTING_SIZE;++e){
			if(h & (1LL << e)) {
				res = max(res, nodes[i].maxw[e]);
				i = nodes[i].par[e];
			}
		}
		return res;
	};
	auto lca = [&](int u, int v) {
		int hu=nodes[u].h, hv=nodes[v].h;
		if(hu>hv){
			u=lift(u, hu-hv);
		} else {
			v=lift(v, hv-hu);
		}
		assert(nodes[u].h == nodes[v].h);
		if (u==v) {
			return u;
		}

		for(int e=BINARY_LIFTING_SIZE-1;e>=0;--e){
			if (nodes[u].par[e] != nodes[v].par[e]) {
				u = nodes[u].par[e];
				v = nodes[v].par[e];
			}
		}

		assert(nodes[u].par[0] == nodes[v].par[0]);
		return nodes[u].par[0];
	};


	for(auto& [a, b, w] : edges) {
		int anc = lca(a, b);
		out<<mstWeight + w - max(maxw(a, nodes[a].h-nodes[anc].h), maxw(b, nodes[b].h-nodes[anc].h))<<"\n";
	}
}
