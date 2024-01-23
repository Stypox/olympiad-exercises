#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int32_t
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

int knapsack(int val[], int wt[], int n, int W) {
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++)
        for (int j = W; j >= wt[i]; j--)
            dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
    return dp[W];
}

signed main() {
	int N,X;
	in>>N>>X;

	int val[N];
	int wt[N];
	for(int n=0;n<N;++n){
		in>>val[n]>>wt[n];
	}

	out<<knapsack(val, wt, N, X);
}
