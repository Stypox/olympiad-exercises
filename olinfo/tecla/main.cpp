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
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

struct Node {
	vec<si> to;
	vec<si> path;
	bool vis = false;
};

int main() {
	si N, M;
	in>>N>>M;
	deb(N,M);

	vec<Node> nodes;
	nodes.resize(N);
	for(int m = 0; m != M; ++m) {
		si from, to;
		in>>from>>to;
		nodes[from].to.push_back(to);
		nodes[to].to.push_back(from);
	}
	nodes[0].vis=true;

	queue<si> process;
	process.push(0);
	while(!process.empty()) {
		si node = process.front();
		for(auto&& to : nodes[node].to) {
			if (!nodes[to].vis) {
				nodes[to].vis = true;
				nodes[to].path = nodes[node].path;
				nodes[to].path.push_back(node);
				process.push(to);
			}
			else if (nodes[to].path.size()%2 == nodes[node].path.size()%2) {
				out<<nodes[to].path.size() + nodes[node].path.size() + 1<<"\n";
				for(auto&& pt : nodes[node].path)
					out<<pt<<" ";
				out<<node<<" "<<to<<" ";
				for(auto pt = nodes[to].path.rbegin(); pt != nodes[to].path.rend(); ++pt)
					out<<*pt<<" ";
				return 0;
			}
		}
		process.pop();
	}
}
