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

struct City{
	int parent=-1, depth=0;
	int x,y;
};

struct Edge{
	int a,b;
	float dist;

	Edge(int a, int b, const vector<City>& c) : a{a}, b{b},
		dist{sqrt((c[a].x-c[b].x)*(c[a].x-c[b].x) + (c[a].y-c[b].y)*(c[a].y-c[b].y))} {}

	bool operator<(const Edge& other) {
		return dist < other.dist;
	}
};

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N,R;
		in>>N>>R;

		vector<City> cities(N);
		for(int n = 0; n != N; ++n) {
			in>>cities[n].x>>cities[n].y;
		}


		function<int(int)> findRoot = [&](int i) -> int {
			deb(i, cities[i].parent);
			if (cities[i].parent == -1) return i;
			return findRoot(cities[i].parent);
		};

		function<bool(int,int)> mergeTrees = [&](int a, int b) -> bool {
			int ra = findRoot(a);
			int rb = findRoot(b);
			if (ra==rb) {
				// cycle detected
				return false;
			} else{
				if (cities[ra].depth > cities[rb].depth) {
					swap(ra,rb);
				}

				cities[ra].parent = rb;
				cities[rb].depth = max(cities[rb].depth, cities[ra].depth + 1);
				return true;
			}
		};


		vector<Edge> edges;
		for(int a = 0; a < N; ++a) {
			for(int b = a+1; b < N; ++b) {
				edges.emplace_back(a, b, cities);
			}
		}
		sort(edges.begin(), edges.end());

		int states=1;
		float roads=0, railroads=0;
		for(auto&& edge : edges) {
			if (mergeTrees(edge.a, edge.b)) {
				if (edge.dist > R) {
					++states;
					railroads+=edge.dist;
				} else {
					roads+=edge.dist;
				}
			}
		}

		out<<"Case #"<<t+1<<": "<<states<<" "<<(int)(roads+0.5)<<" "<<(int)(railroads+0.5)<<"\n";
	}
}
