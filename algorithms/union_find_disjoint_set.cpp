#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int parent=-1;
	int depth=0;
	int money;
};

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N,M;
		in>>N>>M;

		vector<Node> nodes(N);
		function<int(int)> parent = [&](int i) {
			if (nodes[i].parent == -1) return i;
			return parent(nodes[i].parent);
		};
		auto connect = [&](int a, int b) {
			int pa = parent(a);
			int pb = parent(b);
			if (pa==pb) return;

			if (nodes[pa].depth > nodes[pb].depth) swap(pa, pb);
			nodes[pa].parent = pb;
			nodes[pb].depth = max(nodes[pb].depth, 1+nodes[pa].depth);
			nodes[pb].money += nodes[pa].money;
			nodes[pa].money = 0;
		};

		for (int n=0;n<N;++n) {
			in>>nodes[n].money;
		}

		for (int m=0;m<M;++m) {
			int a,b;
			in>>a>>b;
			connect(a,b);
		}

		bool possible=true;
		for (auto&&node:nodes){
			if (node.money!=0) {
				possible=false;
				break;
			}
		}
		out<<(possible?"POSSIBLE\n":"IMPOSSIBLE\n");
	}
}