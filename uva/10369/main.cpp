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
	int parent=-1, depth=0;
	int x,y;
};

struct Edge{
	int a,b;
	float dist;
	Edge(int a, int b, const vector<Node>& nodes) : a{a}, b{b},
		dist{hypotl(nodes[a].x - nodes[b].x, nodes[a].y - nodes[b].y)} {};
	bool operator<(const Edge& other) {
		return dist<other.dist;
	}
};

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int S,P;
		in>>S>>P;

		vector<Node> nodes(P);
		for(int p = 0; p != P; ++p) {
			in>>nodes[p].x>>nodes[p].y;
		}

		vector<Edge> edges;
		for(int a = 0; a < P; ++a) {
			for(int b = a+1; b < P; ++b) {
				edges.emplace_back(a,b,nodes);
			}
		}
		sort(edges.begin(), edges.end());


		function<int(int)> findRoot = [&](int i) {
			if (nodes[i].parent==-1)return i;
			return findRoot(nodes[i].parent);
		};

		int treeCount = P;
		auto mergeTrees = [&](int a, int b){
			int ra=findRoot(a);
			int rb=findRoot(b);
			if (ra==rb) {
				// cycle
				return false;
			} else {
				if (nodes[ra].depth > nodes[rb].depth) {
					swap(ra,rb);
				}
				nodes[ra].parent=rb;
				nodes[rb].depth=max(nodes[rb].depth, nodes[ra].depth+1);

				--treeCount;
				return true;
			}
		};


		float maxDist=0;
		for(auto&& edge : edges) {
			if (treeCount == S) {
				break;
			}
			if (mergeTrees(edge.a, edge.b)) {
				maxDist=max(maxDist,edge.dist);
			}
		}

		out<<(int)maxDist<<"."<<setw(2)<<setfill('0')<<(int)((maxDist-(int)maxDist)*100 + 0.5)<<"\n";
	}
}
