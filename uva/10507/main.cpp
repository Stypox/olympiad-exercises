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
	int year = numeric_limits<int>::max();
	bool counts=false;
	vector<int> activeAround;
	vector<int> edges;
};

struct Item {
	int node,year;
	Item(int node, int year) : node{node}, year{year} {}

	bool operator<(const Item& other) const {
		return year > other.year;
	}
};

string getRemoveA() {
	string s;
	in>>s;
	for (char& c : s) {
		c-='A';
	}
	return s;
}

int32_t main() {
	int N,M;
	in >> N>>M;
	vector<Node> nodes(26);

	string starts = getRemoveA();
	nodes[starts[0]].counts=true;
	nodes[starts[1]].counts=true;
	nodes[starts[2]].counts=true;
	nodes[starts[0]].activeAround={-1,-1,-1};
	nodes[starts[1]].activeAround={-1,-1,-1};
	nodes[starts[2]].activeAround={-1,-1,-1};

	for (int m = 0; m < M; m++) {
		string edge = getRemoveA();
		nodes[edge[0]].counts=true;
		nodes[edge[1]].counts=true;
		nodes[edge[0]].edges.push_back(edge[1]);
		nodes[edge[1]].edges.push_back(edge[0]);
	}
	
	priority_queue<Item> pq;
	pq.emplace(starts[0], 0);
	pq.emplace(starts[1], 0);
	pq.emplace(starts[2], 0);

	while(!pq.empty()) {
		Item item = pq.top();
		pq.pop();
		char a[2] = "A";
		a[0] += (char)item.node;
		deb(a, item.year);

		if (nodes[item.node].year > 10000000 && nodes[item.node].activeAround.size() >= 3) {
			deb("Trying", a);
			int countLastYear=0;
			for (auto e:nodes[item.node].activeAround) {
				countLastYear += ((e==-1) || (nodes[e].year < item.year));
			}

			deb("countLastYear", countLastYear);
			if (countLastYear >= 3) {
				nodes[item.node].year = item.year;
				
				for (int e:nodes[item.node].edges){
					nodes[e].activeAround.push_back(item.node);
					pq.emplace(e, item.year+1);
				}
			}
		}
	}
	

	int maxy=0;
	for(auto&& node:nodes){
		if (node.counts) {
			maxy=max(maxy, node.year);
		}
	}

	if (maxy==numeric_limits<int>::max()) {
		out<<"THIS BRAIN NEVER WAKES UP";
	} else {
		out<<"WAKE UP IN, "<<maxy<<", YEARS";
	}
}
