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

signed main() {
	int N,M;
	cin>>N>>M;
	vector<vector<bool>> mp(N+2, vector<bool>(M+2, false));

	for(int n=0;n<N;++n){
		cin.ignore();
		for(int m=0;m<M;++m){
			char c;
			cin>>c;
			mp[n+1][m+1] = (c=='1');
		}
	}

	N+=2;
	M+=2;

	int res=0;
	vector<vector<bool>> vis(N, vector<bool>(M, false));
	function<void(int,int)> dfs = [&](int x, int y){
		if (x < 0 || y < 0 || x >= N || y >= M) return;
		if (mp[x][y]) {
			++res;
			return;
		}
		if (vis[x][y]) return;
		vis[x][y] = true;

		dfs(x, y+1); dfs(x+1, y);
		dfs(x, y-1); dfs(x-1, y);
	};

	dfs(0,0);
	cout<<res<<"\n";
}
