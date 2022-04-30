#include <bits/stdc++.h>
using namespace std;

#define int long long

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Node {
	int fun;
	int to;
	vector<int> from;

	int currReachableFrom=-1;
	int cycle=-1;
};

signed main() {
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int N;
		cin>>N;

		vector<Node> nodes(N);
		for(int n=0;n<N;++n){
			cin>>nodes[n].fun;
		}

		for(int n=0;n<N;++n){
			cin>>nodes[n].to;
			--nodes[n].to;
		}

		set<int> initiators;
		for(int n=0;n<N;++n){
			if (nodes[n].from.empty()) {
				initiators.insert(n);
			}
		}

		vector<int> sinks;
		for(int i : initiators) {
			function<tuple<int,bool>(int)> dfs = [&](int n) -> tuple<int,bool> {
				if (n == -1 || nodes[n].cycle >= 0) {
					return {-1,false};
				}
				if (nodes[n].currReachableFrom == i) {
					sinks.push_back(n);
					nodes[n].cycle = n;
					return {n,false};
				}
				nodes[n].currReachableFrom = i;

				auto [cycle, alreadyStarted] = dfs(nodes[n].to);
				if (cycle >= 0) {
					if (nodes[n].to == cycle && alreadyStarted) {
						return {-1, false};
					} else {
						nodes[n].cycle = cycle;
						nodes[cycle].fun = max(nodes[cycle].fun, nodes[n].fun);
						return {cycle, true};
					}
				} else {
					assert(nodes[n].cycle < 0);
					return {-1, false};
				}
			};

			dfs(i);
		}

		for (int n=0;n<N;++n){
			if (nodes[n].to == -1) {
				sinks.push_back(n);
			} else if (nodes[n].cycle == -1) {
				if (nodes[nodes[n].to].cycle != -1) {
					nodes[n].to = nodes[nodes[n].to].cycle;
				}
				nodes[nodes[n].to].from.push_back(n);
			}
		}

		int result=0;
		for(int n=0;n<N;++n) deb(n, nodes[n].fun, nodes[n].to, nodes[n].from, nodes[n].cycle);
		deb(sinks, nodes[0].from, nodes[0].cycle, nodes[0].fun);
		for(int sink:sinks){
			function<int(int)> dfs = [&](int n) -> int {
				if (nodes[n].from.empty()) {
					if (nodes[n].cycle == -1) {
						return nodes[n].fun;
					} else {
						assert(n == sink);
						return 0;
					}
				} else if (nodes[n].from.size() == 1) {
					return max(nodes[n].fun, dfs(nodes[n].from[0]));
				} else {
					int sumFroms = 0;
					int minFroms = numeric_limits<int>::max();
					for (auto from:nodes[n].from){
						int fromFun = dfs(from);
						sumFroms += fromFun;
						minFroms = min(minFroms, fromFun);
					}

					result += (sumFroms - minFroms);
					return max(minFroms, nodes[n].fun);
				}
			};
			result += dfs(sink);
		}

		cout<<"Case #"<<t+1<<": "<<result<<"\n";
	}
}
