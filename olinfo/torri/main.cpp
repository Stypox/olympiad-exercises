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

struct Tower {
	int h,c;
};

signed main() {
	int N;
	in>>N;

	vector<Tower> towers(N);
	for(int n=0;n<N;++n){
		in>>towers[n].h>>towers[n].c;
	}

	vector<vector<int>> mem(N, vector<int>(1001, -1));
	function<int(int,int)> rec = [&](int n, int hPrev) -> int {
		if (n >= N) return 0;
		if (mem[n][hPrev] != -1) return mem[n][hPrev];

		if (towers[n].h < hPrev) {
			return mem[n][hPrev] = min(rec(n+1, towers[n].h), rec(n+1, hPrev) + towers[n].c);
		} else {
			return mem[n][hPrev] = rec(n+1, hPrev) + towers[n].c;
		}
	};

	out<<rec(0, 1000)<<"\n";
}
