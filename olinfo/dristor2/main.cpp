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
	constexpr int MOD = 1'000'000'007;
	int N,M;
	in>>N>>M;

	vector<uint16_t> L(M,0);
	for(int n=0;n<N;++n){
		for(int m=0;m<M;++m){
			int i;
			in>>i;
			L[m] |= i<<n;
		}
	}

	bool seen;
	int wantedCnt;
	vector<vector<int>> mem;
	function<int(int, uint16_t)> rec = [&](int m, uint16_t used) -> int {
		if (m >= M) {
			int cnt=0;
			for(int n=0;n<N;++n){
				cnt += ((used & (1<<n)) != 0);
			}
			if (cnt == wantedCnt) {
				seen = true;
			}
			return cnt == wantedCnt;
		}

		if (mem[m][used] == -1) {
			int ways = rec(m+1, used);
			for(int n=0;n<N;++n){
				if ((used & (1<<n)) == 0 && (L[m] & (1<<n)) != 0) {
					ways += rec(m+1, used | (1<<n));
					ways %= MOD;
				}
			}
			mem[m][used] = ways;
		}

		return mem[m][used];
	};

	for(wantedCnt=N; wantedCnt>=0; --wantedCnt) {
		seen=false;
		mem.clear();
		mem.resize(M, vector<int>(1<<N, -1));
		int r=rec(0, 0);
		if (seen) {
			out << r << "\n";
			break;
		}
	}
}
