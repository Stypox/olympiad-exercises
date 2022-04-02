#include <bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int N,M,L;
		cin>>N>>M>>L;

		vector<vector<int>> adj(N);
		for(int m=0;m<M;++m){
			int a,b;
			cin>>a>>b;
			a--;b--;
			adj[a].push_back(b);
		}

		queue<int> q;
		for(int l=0;l<L;++l){
			int c;
			cin>>c;
			c--;
			q.push(c);
		}

		vector<bool> seen(N, false);
		int res=0;
		while(!q.empty()){
			int i=q.front();
			q.pop();

			if(!seen[i]){
				seen[i]=true;
				res++;

				for(auto e:adj[i]){
					q.push(e);
				}
			}
		}

		cout<<res<<"\n";
	}
}