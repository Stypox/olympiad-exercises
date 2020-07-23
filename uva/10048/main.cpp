
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
	int mindb;
	vector<pair<int,int>> conn;
};

struct Item{
	int i,newdb;
	bool operator<(const Item& other) const {
		return newdb>other.newdb;
	}
};

int32_t main() {
	int t=0;
	while(1){
		int C,S,Q;
		in>>C>>S>>Q;
		if(C==0&&S==0&&Q==0)break;
		++t;

		vector<Node> nodes(C);
		for(int s = 0; s != S; ++s) {
			int a,b,w;
			in>>a>>b>>w;--a;--b;
			nodes[a].conn.emplace_back(b,w);
			nodes[b].conn.emplace_back(a,w);
		}


		if (t!=1)out<<"\n";
		out<<"Case #"<<t<<"\n";
		for(int q = 0; q != Q; ++q) {
			for(int c = 0; c != C; ++c) {
				nodes[c].mindb=numeric_limits<int>::max();
			}
			int a,b;
			in>>a>>b;--a;--b;

			priority_queue<Item> pq;
			pq.push({a,0});
			while(!pq.empty()) {
				Item item = pq.top();
				pq.pop();

				if (item.newdb < nodes[item.i].mindb) {
					nodes[item.i].mindb=item.newdb;

					for(auto&& con : nodes[item.i].conn) {
						pq.push({con.first, max(item.newdb,con.second)});
					}
				}
			}

			if (nodes[b].mindb != numeric_limits<int>::max()) {
				out<<nodes[b].mindb<<"\n";
			} else {
				out<<"no path\n";
			}
		}
	}
}
