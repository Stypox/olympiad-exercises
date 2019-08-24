#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

constexpr si nothing=0, white=1, black=2;

struct Node {
	si n;
	si col=nothing;
	vec<si> cons;
};

vec<si> bestBlack;

vec<Node> nodes;
void rec(si i) {
	if (nodes[i].col == black)
		for(auto&& con : nodes[i].cons)
			if (nodes[con].col == black)
				return;

	if(i==(nodes.size()-1)) {
		vec<si> blackNodes;
		for(auto&& node : nodes)
			if (node.col == black)
				blackNodes.push_back(node.n);
		
		if (blackNodes.size() > bestBlack.size())
			bestBlack = blackNodes;
		return;
	}

	nodes[i+1].col = black;
	rec(i+1);
	nodes[i+1].col = white;
	rec(i+1);
	nodes[i+1].col = nothing;
}

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si N,K;
		in>>N>>K;

		nodes.resize(0);
		nodes.resize(N);
		for(int n = 0; n < N; ++n)
			nodes[n].n=n;
		
		for(int k = 0; k != K; ++k) {
			si a,b;
			in>>a>>b;
			a--; b--;
			nodes[a].cons.push_back(b);
			nodes[b].cons.push_back(a);
		}
		

		bestBlack.resize(0);
		nodes[0].col=white;
		rec(0);
		nodes[0].col=black;
		rec(0);

		out<<bestBlack.size()<<"\n"<<bestBlack[0]+1;
		for(int i = 1; i != bestBlack.size(); ++i) {
			out<<" "<<bestBlack[i]+1;
		}
		out<<"\n"<<flush;
	}
}
