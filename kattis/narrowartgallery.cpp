#include <bits/stdc++.h>
using namespace std;

int main(){
	while(1){
		int N,K;
		cin>>N>>K;
		if(N==0&&K==0) break;

		vector<vector<int>> V(N, vector<int>(2));
		for(int n=0;n<N;++n){
			cin>>V[n][0]>>V[n][1];
		}

		vector<vector<vector<int>>> mem(N, vector<vector<int>>(K+1, vector<int>(2,-1)));
		function<int(int, int, bool)> rec = [&](int n, int k, bool side) -> int {
			if(n>=N) return k==0 ? 0 : numeric_limits<int>::min()/4;
			if(mem[n][k][side] == -1) {
				mem[n][k][side] = V[n][0] + V[n][1] + max(rec(n+1, k, false), rec(n+1, k, true));
				if(k!=0){
					mem[n][k][side] = max(mem[n][k][side], V[n][side] + rec(n+1, k-1, side));
				}
			}
			return mem[n][k][side];
		};
		cout<<max(rec(0,K,false), rec(0,K,true))<<"\n";
	}
}