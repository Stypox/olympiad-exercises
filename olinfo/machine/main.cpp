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
	int C,D,Y;
	in>>C>>D>>Y;
	vector<int> M(D), P(D);
	for(int d=0;d<D;++d) in>>M[d];
	for(int d=0;d<D;++d) in>>P[d];

	vector<int> knapsack(D+1);
	knapsack[1] = C + M[0] - P[0];
	for(int d=1;d<D;++d){
		knapsack[d+1] = knapsack[d] + M[d] + P[d-1] - P[d];
	}
	deb(knapsack);

	Y++;
	vector<int> mem(Y, 0);
	for(int y=Y-2; y>=0; y--) {
		mem[y]=numeric_limits<int>::max();
		for(int d=1;d<=min(D, Y-y);++d){
			mem[y]=min(mem[y], knapsack[d] + mem[y+d]);
		}
	}

	out<<mem[0]<<"\n";
}
