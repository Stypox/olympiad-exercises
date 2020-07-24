#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node{
	int parent=-1,depth=0; // needed for union-find disjoint sets and for minimum spanning tree
	vector<pair<int,int>> mstNeighbors; // [i] -> edge to mstConn[i].first of weight mstConn[i].second
	vector<int> maxWeightEdgeTo; // [i] -> maximum weight of mst edges to reach nodes[i]
};

struct Edge{
	int a,b,w; // edge (a,b) of weight w
	bool usedInMst=false; // to prevent substituting an edge with itself
	bool operator<(const Edge& other) {
		return w<other.w; // sort edges by non-decreasing weight
	}
};

int32_t main() {
	int T;
	cin >> T;

	for(int t = 0; t != T; ++t) {
		int N,M;
		cin>>N>>M;

		vector<Node> nodes(N);
		vector<Edge> edges(M);
		for(int m = 0; m != M; ++m) {
			cin>>edges[m].a>>edges[m].b>>edges[m].w;
			// transform from 1-indexed to 0-indexed
			--edges[m].a;--edges[m].b;
		}


		// Union-find disjoint sets functions
		// i: index of the node to find the root of
		function<int(int)> findRoot = [&](int i){
			if (nodes[i].parent==-1)return i;
			return findRoot(nodes[i].parent);
		};

		// edge: the edge containing the two vertices to connect
		function<bool(Edge&)> mergeTrees = [&](Edge& edge){
			int ra=findRoot(edge.a);
			int rb=findRoot(edge.b);

			if (ra==rb){
				// cycle detected, this edge cannot be used
				return false;
			} else {
				if (nodes[ra].depth>nodes[rb].depth) {
					// ensure node with smaller depth gets that with bigger depth as parent
					swap(ra,rb);
				}

				nodes[ra].parent=rb;
				nodes[rb].depth=max(nodes[rb].depth,nodes[ra].depth+1);
				nodes[ra].mstNeighbors.push_back({rb,edge.w});
				nodes[rb].mstNeighbors.push_back({ra,edge.w});
				return true;
			}
		};

		// sort edges to find minimum spanning tree greedily -> O(E log E) = O(V² log V)
		sort(edges.begin(), edges.end());

		// find cost of minimum spanning tree using Kruskal's -> O(E) = O(V²)
		// for every node in the mst store its tree neighbors (i.e. the parent and all children)
		int cost1=0;
		for(auto&& edge : edges) {
			if(mergeTrees(edge)){
				// this edge was just connected, so count it in the mst
				edge.usedInMst=true;
				cost1+=edge.w;
			}
		}


		// tree traversal from a single source to every other vertex in the minimum spanning tree -> O(V²)
		// i: node index  before: calling node index  start: search root node index  maxWeight: max edge weight so far
		function<void(int,int,int,int)> populateMaxWeightEdgeTo = [&](int i,int before,int start,int maxWeight) {
			nodes[start].maxWeightEdgeTo[i]=maxWeight;
			for(auto&& con : nodes[i].mstNeighbors) {
				if (con.first != before) {
					// go to (one of) the next connected vertex(es)
					populateMaxWeightEdgeTo(con.first, i, start, max(maxWeight,con.second));
				}
			}
		};

		for(int n = 0; n != N; ++n) {
			// traverse entire tree starting from node n and store the maximum weight
			// of the edges connecting node n to all other nodes
			nodes[n].maxWeightEdgeTo.resize(N);
			populateMaxWeightEdgeTo(n,-1,n,0);
		}


		// finding cost of second minimum spanning tree -> O(E) = O(V²)
		int cost2=numeric_limits<int>::max();
		for(auto&& edge : edges) {
			if (!edge.usedInMst) {
				// for every edge not belonging to the mst, try disconnecting the two
				// vertices it connects by removing the mst edge with the maximum weight
				// in between the two vertices, and then reconnecting them with the
				// currently considered vertex. Store the minimum result.
				int cost = cost1 + edge.w - nodes[edge.a].maxWeightEdgeTo[edge.b];
				cost2 = min(cost2, cost);
			}
		}

		cout<<cost1<<" "<<cost2<<"\n";
	}
}
