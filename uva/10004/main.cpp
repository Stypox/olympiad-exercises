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
	int color=-1;
	vector<int> conn;
};

int32_t main() {
	while(1){
		int N,L;
		in>>N;
		if(N==0) break;
		in>>L;

		vector<Node> nodes(N);
		for(int l = 0; l != L; ++l) {
			int a,b;
			in>>a>>b;
			nodes[a].conn.push_back(b);
			nodes[b].conn.push_back(a);
		}

		queue<pair<int,int>> q;
		q.push({0,0});
		bool doable=true;
		while (!q.empty()) {
			auto [i,c] = q.front();
			deb(i,c);
			q.pop();

			if (nodes[i].color == -1) {
				nodes[i].color=c;
				for(auto&& con : nodes[i].conn) {
					q.push({con, (c+1)%2});
				}
			} else {
				if (nodes[i].color!=c) {
					doable=false;
					break;
				}
			}
		}

		deb();
		out<<(doable?"BICOLORABLE.\n":"NOT BICOLORABLE.\n");
	}
}
