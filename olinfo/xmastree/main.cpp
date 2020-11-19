#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

struct Node {
	int parent = -1;
	vector<int> children;
	int max0, max1;
	int A;
};

int32_t main() {
	int N;
	in>>N;

	vector<Node> nodes(N);
	for(int n=0;n<N-1;++n){
		int a,b;
		in>>a>>b;
		if (b>a) swap(a,b);
		if (nodes[a].parent != -1) swap(a,b);
		nodes[a].parent=b;
		nodes[b].children.push_back(a);
	}

	for (int n=0;n<N;++n){
		in>>nodes[n].A;
	}

	function<void(int)> rec = [&](int i) {
		if (nodes[i].children.empty()) {
			nodes[i].max0=0;
			nodes[i].max1=nodes[i].A;
			return;
		}

		int minDelta = numeric_limits<int>::max(), val = 0;
		bool parity = false;
		for (int child : nodes[i].children) {
			rec(child);
			if (nodes[child].max0 > nodes[child].max1) {
				val += nodes[child].max0;
				parity = !parity;
			} else {
				val += nodes[child].max1;
			}

			minDelta = min(minDelta, abs(nodes[child].max0 - nodes[child].max1));
		}

		if (parity) {
			nodes[i].max0 = val;
			nodes[i].max1 = val + nodes[i].A - minDelta;
		} else {
			nodes[i].max0 = val - minDelta;
			nodes[i].max1 = val + nodes[i].A;
		}
	};

	rec(0);
	out<<max(nodes[0].max0, nodes[0].max1)<<"\n";
}
