#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int dist=numeric_limits<int>::max();
	vector<pair<int, int>> conn;
};

int main() {
	int N,M,A,B;
	in>>N>>M>>A>>B; A--; B--;

	vector<Node> nodes(N);
	for(int m = 0; m != M; ++m) {
		int a,b,w;
		in>>a>>b>>w; a--; b--;
		nodes[a].conn.push_back({b,w});
	}

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
	nodes[A].dist = 0;
	pq.push({0, A});

	while(!pq.empty()) {
		auto [dist, i] = pq.top();
		pq.pop();

		if (dist != nodes[i].dist) continue;
		deb(dist, i);

		for(auto [to, w] : nodes[i].conn) {
			if (dist + w < nodes[to].dist) {
				nodes[to].dist = dist + w;
				pq.push({nodes[to].dist, to});
			}
		}
	}

	out<<nodes[B].dist;
}
