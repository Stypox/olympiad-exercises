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

struct Node {
	int parent=-1, rank=0;
};

struct UFDS {
	vector<Node> nodes;
	UFDS(int N) : nodes(N) {}

	int findParent(int a) {
		if (nodes[a].parent == -1) return a;
		return findParent(nodes[a].parent);
	}

	void join(int a, int b) {
		int pa = findParent(a);
		int pb = findParent(b);
		if (pa==pb) return;

		if (nodes[pa].rank > nodes[pb].rank) {
			swap(pa, pb);
		}

		nodes[pa].parent = pb;
		nodes[pb].rank = nodes[pa].rank + 1;
	}

	int countParents() {
		return count_if(nodes.begin(), nodes.end(), [](const Node& n) {return n.parent == -1; });
	}
};

int32_t main() {
	int t=0;
	while(1){
		int N,M;
		in>>N>>M;
		if(N==0) break;
		++t;

		UFDS ufds{N};
		for(int m=0;m<M;++m){
			int a,b;
			in>>a>>b;
			--a; --b;

			ufds.join(a,b);
		}

		out<<"Case "<<t<<": "<<ufds.countParents()<<"\n";
	}
}
