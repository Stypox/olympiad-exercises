#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct P{
	int cash;
	int time;
};

ostream&operator<<(ostream&o,const P&p){cerr<<"("<<p.cash<<", "<<p.time<<")";return o;}

signed main() {
	int N,T;
	cin>>N>>T;

	vector<P> ppl(N);
	for(int n=0;n<N;++n){
		cin>>ppl[n].cash>>ppl[n].time;
	}

	deb(N, T, ppl);
	sort(ppl.begin(), ppl.end(), [](P&a,P&b){return a.time<b.time;});

	vector<vector<int>> mem(T, vector<int>(N, -1));
	function<int(int,int)> rec = [&](int t, int n) -> int {
		if (n>=N) return 0;
		if (t>=T) return 0; // TODO check >

		if (mem[t][n] == -1) {
			if (t > ppl[n].time) {
				// TODO check >=
				mem[t][n] = rec(t, n+1);
			} else {
				mem[t][n] = max(ppl[n].cash + rec(t+1, n+1), rec(t, n+1));
			}
		}

		return mem[t][n];
	};

	rec(0,0);
	deb(mem);

	cout << rec(0,0) << "\n";
}
