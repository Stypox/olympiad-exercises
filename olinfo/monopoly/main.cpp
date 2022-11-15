#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int N,K;
	in>>N>>K;

	vector<int> T(N);
	for(int n=0;n<N;++n) {
		in>>T[n];
	}

	vector<vector<vector<int>>> mem(N, vector<vector<int>>(K, vector<int>(3, -1)));
	function<int(int,int,int)> maxSpesa = [&](int n, int k, int m) -> int {
		if (k>=K) {
			return 0;
		} else if (mem[n][k][m] != -1) {
			return mem[n][k][m];
		}

		int maxhere = numeric_limits<int>::min() / 8;
		for (int i=2;i<=12;++i){
			int p = (n+i)%N;
			if ((i != 2 && i != 12) || m == 0) {
				maxhere = max(maxhere, T[p] + maxSpesa(p, k+1, 2));
			}
			if (i % 2 == 0 && m > 0) {
				maxhere = max(maxhere, T[p] + maxSpesa(p, k, m-1));
			}
		}

		mem[n][k][m] = maxhere;
		return maxhere;
	};

	out<<maxSpesa(0,0,2)<<"\n";
}
