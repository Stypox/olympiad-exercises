#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

struct Con{
	int to,l;
};

int main(){
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N,M;
		cin>>N>>M;

		vector<vector<Con>> adj(N);
		for(int m=0;m<M;++m){
			int a,b,l;
			cin>>a>>b>>l;
			adj[a].push_back({b,l});
			adj[b].push_back({a,l});
		}

		auto dijkstra = [&](int from) {
			vector<int> minSoFar(N,numeric_limits<int>::max()/10);
			priority_queue<pii, vector<pii>, greater<pii>> pq;
			pq.push({0,from});

			while(!pq.empty()) {
				auto [d, n] = pq.top();
				pq.pop();

				if (d<minSoFar[n]){
					minSoFar[n]=d;
					for(auto [to,l] : adj[n]){
						pq.push({d+l, to});
					}
				}
			}

			return minSoFar;
		};


		int I;
		cin>>I;
		vector<int> P(I+1,0);
		for(int i=0;i<I;++i){
			cin>>P[i+1];
		}

		int A;
		cin>>A;

		vector<vector<int>> dists(P.size(), vector<int>(P.size()));
		for(int i=0;i<P.size();++i){
			vector<int> minDistances = dijkstra(P[i]);
			for(int j=0;j<P.size();++j) {
				dists[i][j] = minDistances[P[j]];
			}
		}

		vector<int> treasures(I);
		iota(treasures.begin(), treasures.end(), 1);
		int maxTreasuresSoFar=0;
		do{
			for(int i=1;i<=I;++i){
				int airUsed = dists[0][treasures[0]] + dists[treasures[i-1]][0];
				for(int j=0;j<i-1;++j){
					airUsed += dists[treasures[j]][treasures[j+1]];
				}
				if(airUsed <= A) {
					maxTreasuresSoFar = max(maxTreasuresSoFar, i);
				}
			}
		}while(next_permutation(treasures.begin(), treasures.end()));

		cout<<maxTreasuresSoFar<<"\n";
	}
}