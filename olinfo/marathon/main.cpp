#include <bits/stdc++.h>
using namespace std;

constexpr int BINARY_LIFTING_SIZE = 20;


int higherPowerOf2(int x) {
	int res = 1;
	while (res < x) res *= 2;
	return res;
}

struct SegmentTree {
	vector<int> data;
	SegmentTree(int n) : data(2 * higherPowerOf2(n), 0) {}

	int query(int i, int a, int b, int x, int y) {
		if (b <= x || a >= y) return 0;
		if (b <= y && a >= x) return data[i];

		return query(i*2,   a, (a+b)/2, x, y)
		     + query(i*2+1, (a+b)/2, b, x, y);
	}

	int update(int i, int a, int b, int x, int v) {
		if (x < a || x >= b) return data[i];
		if (a == b-1) {
			assert(a == x);
			return data[i] = v;
		}

		return data[i] = update(i*2,   a, (a+b)/2, x, v)
			            + update(i*2+1, (a+b)/2, b, x, v);
	}

	int query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

	void update(int x, int v) {
		update(1, 0, data.size()/2, x, v);
	}
};

struct Node {
	int depth;
	int parents[BINARY_LIFTING_SIZE];
	int enterTime, exitTime;
	bool roadToParentActive = true;
};


vector<vector<int>> adj;
int dfsTime;
vector<Node> nodes;
SegmentTree edgesSegTree(0);

void depthFirstSearch(int n, int parent, int depth) {
	nodes[n].depth = depth;
	nodes[n].parents[0] = parent;
	for (int i = 1; i < BINARY_LIFTING_SIZE; ++i) {
		nodes[n].parents[i] = nodes[nodes[n].parents[i-1]].parents[i-1];
	}

	nodes[n].enterTime = dfsTime;
	for (int e : adj[n]) {
		if (e != parent) {
			edgesSegTree.update(dfsTime, 1);
			++dfsTime;
			depthFirstSearch(e, n, depth + 1);
			edgesSegTree.update(dfsTime, -1);
			++dfsTime;
		}
	}
	nodes[n].exitTime = dfsTime;
}

int raiseBy(int x, int deltaDepth) {
	for (int i = BINARY_LIFTING_SIZE - 1; i >= 0; --i) {
		if ((1 << i) <= deltaDepth) {
			x = nodes[x].parents[i];
			deltaDepth -= (1 << i);
		}
	}
	return x;
}

int lowestCommonAncestor(int x, int y) {
	if (nodes[x].depth > nodes[y].depth) swap(x, y);
	y = raiseBy(y, nodes[y].depth - nodes[x].depth);
	if (x == y) {
		return x;
	}

	for (int i = BINARY_LIFTING_SIZE - 1; i >= 0; --i) {
		if (nodes[x].parents[i] != nodes[y].parents[i]) {
			x = nodes[x].parents[i];
			y = nodes[y].parents[i];
		}
	}

	assert(x != y);
	assert(nodes[x].parents[0] == nodes[y].parents[0]);
	return nodes[x].parents[0];
}


int main() {
	int N, Q;
	cin >> N >> Q;

	adj.resize(N);
	dfsTime = 0;
	nodes.resize(N);
	edgesSegTree = SegmentTree(N*2-2);

	for (int n = 0; n < N-1; ++n) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	depthFirstSearch(0, 0, 0);
	assert(dfsTime == N*2-2);

	int sum = 0;
	for (int q = 0; q < Q; ++q) {
		int type, x, y;
		cin >> type >> x >> y;

		if (type == 1) {
			--x; --y;
			if (y == nodes[x].parents[0]) swap(x, y);

			nodes[y].roadToParentActive = !nodes[y].roadToParentActive;
			int valToSet = nodes[y].roadToParentActive ? 1 : 0;
			edgesSegTree.update(nodes[y].enterTime - 1,  valToSet);
			edgesSegTree.update(nodes[y].exitTime,      -valToSet);

		} else {
			assert(type == 2);
			x = (x + sum) % N;
			y = (y + sum) % N;

			int lca = lowestCommonAncestor(x, y);
			int edgesSum = abs(edgesSegTree.query(nodes[lca].enterTime, nodes[x].enterTime))
			             + abs(edgesSegTree.query(nodes[lca].enterTime, nodes[y].enterTime));
			int pathLength = nodes[x].depth + nodes[y].depth - 2 * nodes[lca].depth;
			assert(pathLength >= edgesSum);

			if (pathLength == edgesSum) {
				cout << 1 << endl;
				++sum;
			} else {
				cout << 0 << endl;
			}
		}
	}
}
