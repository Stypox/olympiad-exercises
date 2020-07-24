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


struct Edge{
	int to,weight;
};

struct Node{
	int price;
	vector<Edge> edges;
	vector<int> money;
};

struct Item{
	int money, i, fuel;
	bool operator<(const Item& item) const {
		return money > item.money;
	}
};


int32_t main() {
	int N,M;
	in>>N>>M;

	vector<Node> nodes(N);
	for(int n = 0; n != N; ++n) {
		in>>nodes[n].price;
	}

	for(int m = 0; m != M; ++m) {
		int a,b,w;
		in>>a>>b>>w;
		nodes[a].edges.push_back({b,w});
		nodes[b].edges.push_back({a,w});
	}


	int Q;
	in>>Q;
	for(int q = 0; q != Q; ++q) {
		int C,S,E;
		in>>C>>S>>E;

		for(int n = 0; n != N; ++n) {
			nodes[n].money.clear();
			nodes[n].money.resize(C+1,numeric_limits<int>::max());
		}


		priority_queue<Item> pq;
		pq.push({0,S,0});
		while(!pq.empty()){
			Item item = pq.top();
			pq.pop();

			if (item.money < nodes[item.i].money[item.fuel]) {
				nodes[item.i].money[item.fuel] = item.money;

				for(auto&& edge : nodes[item.i].edges) {
					int newFuel = item.fuel - edge.weight;
					if (newFuel >= 0 && item.money < nodes[edge.to].money[newFuel]) {
						pq.push({item.money, edge.to, newFuel});
					}
				}

				int newMoney = item.money + nodes[item.i].price;
				if (item.fuel < C && newMoney < nodes[item.i].money[item.fuel+1]) {
					pq.push({newMoney, item.i, item.fuel+1});
				}
			}
		}

		if (nodes[E].money[0] == numeric_limits<int>::max()) {
			out<<"impossible\n";
		} else {
			out<<nodes[E].money[0]<<"\n";
		}
	}
}
