#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<int>& D) {
	vector<vector<pair<int,int>>> adj(N);
	for(int m=0;m<M;++m){
		adj[X[m]].push_back({Y[m], P[m]});
	}
	fill(D.begin(), D.end(), numeric_limits<int>::max());

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq(greater<pair<int,int>>{});
	pq.push({0,0});
	D[0]=0;
	while(!pq.empty()) {
		auto [d,i] = pq.top();
		pq.pop();

		if (d==D[i]) {
			for(auto [e,p]:adj[i]) {
				int r=d+p;
				if (r < D[e]) {
					D[e] = r;
					pq.push({r,e});
				}
			}
		}
	}

	for(auto& d:D){
		if(d==numeric_limits<int>::max()) d=-1;
	}
}
