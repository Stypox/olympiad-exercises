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

struct Server {
	int P,S,tasks;
};

int32_t main() {
	int T;
	in>>T;
	for(int t=0;t<T;++t){
		int K,N,M;
		in>>N>>K>>M;

		vector<Server> servers(N);
		int maxP=-1, maxS=-1;
		for(auto&& server : servers) {
			in>>server.P>>server.S;
			maxP=max(maxP, server.P);
			maxS=max(maxS, server.S);
		}

		auto calTasks = [&](int time) {
			for (auto&& server : servers) {
				server.tasks = max((int)0, (time - server.P) / server.S);
			}
			sort(servers.begin(), servers.end(), [](Server&a,Server&b){return a.tasks>b.tasks;});

			int totTasks = 0;
			for(int k = 0; k != K; ++k) {
				totTasks+=servers[k].tasks;
				if (totTasks >= M) break;
			}
			return totTasks;
		};

		int t1=0,t2=maxP+M*maxS+1LL;
		while(1) {
			int time = (t1+t2)/2;

			int totTasks = calTasks(time);
			deb(t1,t2,"=",time,"->",totTasks);
			if (totTasks >= M) {
				t2 = time+1;
			} else {
				t1 = time+1;
			}

			if ((t1+1) == t2) {
				break;
			} else if ((t1+2) == t2) {
				int a1=calTasks(t1);
				if(a1 >= M) {
					break;
				} else {
					t1++;
					break;
				}
			}
		}

		deb("\n");
		out<<"Case #"<<t+1<<": "<<t1<<"\n";
	}
}
