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
	si dist=numeric_limits<si>::max();
	vec<pair<si, si>> conn;
};

int main() {
	si N,M,A,B;
	in>>N>>M>>A>>B; A--; B--;

	vec<Node> nodes(N);
	for(si m = 0; m != M; ++m) {
		si a,b,w;
		in>>a>>b>>w; a--; b--;
		nodes[a].conn.push_back({b,w});
	}

	priority_queue<pair<si,si>, vector<pair<si,si>>, greater<pair<si, si>>> pq;
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
