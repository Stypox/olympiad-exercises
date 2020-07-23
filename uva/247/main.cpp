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
	string name;
	bool seen1=false,seen2=false;
	int connectedComponent=-1;
	vector<int> to, from;
};

int32_t main() {
	int T=0;
	while(1){
		++T;
		int N,M;
		in>>N>>M;
		if(N==0)break;

		int counter=0;
		map<string, int> namemap;
		vector<Node> nodes(N);
		for(int m = 0; m != M; ++m) {
			string sa,sb;
			in>>sa>>sb;

			if (namemap.count(sa) == 0) {
				namemap[sa]=counter;
				nodes[counter].name=sa;
				++counter;
			}
			if (namemap.count(sb) == 0) {
				namemap[sb]=counter;
				nodes[counter].name=sb;
				++counter;
			}
			int a=namemap[sa],b=namemap[sb];

			nodes[a].to.push_back(b);
			nodes[b].from.push_back(a);
		}


		vector<int> outOrder;
		function<void(int)> dfs1 = [&](int i){
			nodes[i].seen1=true;
			for(auto&& edge : nodes[i].to) {
				if (!nodes[edge].seen1) {
					dfs1(edge);
				}
			}
			outOrder.push_back(i);
		};

		for(int n = 0; n != N; ++n) {
			if (!nodes[n].seen1) {
				dfs1(n);
			}
		}


		vector<int> connectedComponent;
		function<void(int)> dfs2 = [&](int i) {
			nodes[i].seen2=true;
			connectedComponent.push_back(i);
			for(auto&& edge : nodes[i].from) {
				if (!nodes[edge].seen2) {
					dfs2(edge);
				}
			}
		};

		if (T!=1) {
			out<<"\n";
		}
		out<<"Calling circles for data set "<<T<<":\n";
		for(auto it = outOrder.rbegin(); it != outOrder.rend(); ++it) {
			if (!nodes[*it].seen2) {
				connectedComponent.clear();
				dfs2(*it);

				if (connectedComponent.size() == 1 && nodes[*it].from.size() == 0 && nodes[*it].to.size() == 0) {
					continue;
				}

				for(int i = 0; i != connectedComponent.size(); ++i) {
					if (i!=0)out<<", ";
					out<<nodes[connectedComponent[i]].name;
				}
				out<<"\n";
			}
		}
	}
}
