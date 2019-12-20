#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

struct Node {
	si parent;
	si brig;
	vec<si> children;

	vec<si> stNodes, stMax;
	si tin,tout;
};

vec<Node> getTree(int N, int*briganti, int*A, int*B){
	vec<Node> nodes(N);

	for(int n=0;n<(N-1);++n){
		if(A[n]>B[n]) swap(A[n],B[n]);
		nodes[A[n]].children.push_back(B[n]);
		nodes[B[n]].parent = A[n];
	}

	for(int n=0;n<N;++n){
		nodes[n].brig=briganti[n];
	}

	nodes[0].parent=0;
	return nodes;
}

void buildTables(vec<Node>& nodes, const si& logN) {
	for(auto&& node:nodes) {
		node.stNodes.push_back(node.parent);
		node.stMax.push_back(node.brig);
	}

	si pow2=0;
	while(1){
		deb("\npow2:",pow2);
		for(auto&& node:nodes) {
			deb("b", node.brig, node.stNodes[pow2]);
			node.stNodes.push_back(nodes[node.stNodes[pow2]].stNodes[pow2]);
			node.stMax.push_back(max(nodes[node.stNodes[pow2]].stMax[pow2],node.stMax[pow2]));
		}
		pow2++;
		if(pow2>logN)break;
	}
}

void buildTimes(vec<Node>& nodes) {
	si t=0;
	function<void(si)> dfs = [&dfs, &nodes, &t](si i){
		nodes[i].tin=t++;
		for(si child:nodes[i].children)
			dfs(child);
		nodes[i].tout=t++;
	};
	dfs(0);
}

void solve(int N, int Q, int *briganti, int *A, int *B, int *start, int *end, int *sol) {
	si logN = ceil(log2(N));
	vec<Node> nodes=getTree(N,briganti,A,B);

	buildTables(nodes, logN);
	buildTimes(nodes);

	auto isAncestor = [&nodes](si u, si v) {
		// is v an ancestor of u?
		return nodes[u].tin <= nodes[v].tin && nodes[u].tout >= nodes[v].tout;
	};
	auto lca = [&nodes, &isAncestor, &logN](si u, si v) {
		if (isAncestor(u, v)) {
			return u;
		}
		if (isAncestor(v, u)) {
			return v;
		}

		for (int i = logN; i >= 0; --i) {
			if (!isAncestor(nodes[u].stNodes[i], v)) {
				u = nodes[u].stNodes[i];
			}
		}
		return nodes[u].stNodes[1];
	};

	auto maxFrom = [&nodes,&logN,&isAncestor](si u, si a) {
		si m=nodes[u].brig;
		
		deb("maxFrom",u,a);
		for(int i=logN; i>=0; --i){
			deb(i, nodes[u].stNodes[i], a);
			if(isAncestor(a, nodes[u].stNodes[i])) {
				deb("yes");
				m = max(m, nodes[u].stMax[i]);
				u = nodes[u].stNodes[i];
			}
		}

		return m;
	};

#ifdef DEBUG
	for(auto&& node:nodes){
		cout<<"parent:"<<node.parent<<" brig:"<<node.brig<<" tin:"<<node.tin<<" tout:"<<node.tout<<"\n";
		debc(node.stNodes, "stNodes: ");
		debc(node.stMax, "stMax: ");
	}
#endif

	for(int q=0;q<Q;++q){
		si u = start[q], v = end[q];
		si anc = lca(u,v);
		deb("query", u, v, "-> anc", anc);
		sol[q] = max(maxFrom(u,anc), maxFrom(v,anc));
	}
}
