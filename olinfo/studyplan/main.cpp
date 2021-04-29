#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) {cout<<"[";for(size_t i=0;i<v.size();++i){if(i!=0){cout<<",";}cout<<v[i];}cout<<"]";return o;}
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

struct Node{
	int h;
	int fromcount=0;
	vector<int> to;
	int used=0;
	int t=-1;
};

int32_t main() {
	int N;
	in>>N;

	vector<Node> nodes(N);
	for(int n=0;n<N;++n){
		in>>nodes[n].h;
	}

	for(int n=0;n<N;++n){
		int K;
		in>>K;
		for(int k=0;k<K;++k){
			int dep;
			in>>dep;
			nodes[dep].fromcount++;
			nodes[n].to.push_back(dep);
		}
	}

	queue<pair<int,int>> q;
	for(int n=0;n<N;++n){
		if(nodes[n].fromcount==0) {
			q.push({n, 0});
		}
	}

	while(!q.empty()) {
		auto [i, t] = q.front();
		q.pop();
		nodes[i].t = max(nodes[i].t, t);

		++nodes[i].used;
		if (nodes[i].used >= nodes[i].fromcount) {
			for(auto p : nodes[i].to) {
				q.push({p, nodes[i].t + nodes[i].h});
			}
		}
	}

	int maxt=-1;
	for(int n=0;n<N;++n){
		maxt = max(maxt, nodes[n].t + nodes[n].h);
	}
	deb(maxt);

	for(int n=0;n<N;++n){
		out << maxt-nodes[n].h-nodes[n].t << " ";
		deb(n, nodes[n].h, nodes[n].fromcount, nodes[n].to, "->", nodes[n].t);
	}
}
