#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

struct Node{
	int parent=-1,depth=0;
	vector<pair<int,int>> mstConn;
	vector<int> maxWeightEdgeTo;
};

struct Edge{
	int a,b,w;
	bool usedInMst=false;
	bool operator<(const Edge& other) {
		return w<other.w;
	}
};

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N,M;
		in>>N>>M;

		vector<Node> nodes(N);
		vector<Edge> edges(M);
		for(int m = 0; m != M; ++m) {
			in>>edges[m].a>>edges[m].b>>edges[m].w;
			--edges[m].a;--edges[m].b;
		}
		sort(edges.begin(), edges.end());

		function<int(int)> findRoot = [&](int i){
			if (nodes[i].parent==-1)return i;
			return findRoot(nodes[i].parent);
		};
		function<bool(Edge&)> mergeTrees = [&](Edge& edge){
			int ra=findRoot(edge.a);
			int rb=findRoot(edge.b);

			if (ra==rb){
				// cycle
				return false;
			} else {
				if (nodes[ra].depth>nodes[rb].depth) {
					swap(ra,rb);
				}

				nodes[ra].parent=rb;
				nodes[rb].depth=max(nodes[rb].depth,nodes[ra].depth+1);
				nodes[ra].mstConn.push_back({rb,edge.w});
				nodes[rb].mstConn.push_back({ra,edge.w});
				edge.usedInMst=true;
				return true;
			}
		};

		int cost1=0;
		for(auto&& edge : edges) {
			if(mergeTrees(edge)){
				cost1+=edge.w;
			}
		}


		function<void(int,int,int,int)> populateMaxWeightEdgeTo = [&](int i,int before,int start,int maxWeight) {
			nodes[start].maxWeightEdgeTo[i]=maxWeight;
			for(auto&& con : nodes[i].mstConn) {
				if (con.first != before) {
					populateMaxWeightEdgeTo(con.first,i,start,max(maxWeight,con.second));
				}
			}
		};

		for(int n = 0; n != N; ++n) {
			nodes[n].maxWeightEdgeTo.resize(N);
			populateMaxWeightEdgeTo(n,-1,n,0);
		}


		int cost2=numeric_limits<int>::max();
		for(auto&& edge : edges) {
			if (!edge.usedInMst) {
				int cost = cost1 + edge.w - nodes[edge.a].maxWeightEdgeTo[edge.b];
				cost2 = min(cost2, cost);
			}
		}

		out<<cost1<<" "<<cost2<<"\n";
	}
}
