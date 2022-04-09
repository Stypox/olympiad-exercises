#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;

struct Node{
	vector<pii> conn;
	int minDist=numeric_limits<int>::max();
};

int main(){
	while(1){
		int N,M,Q,S;
		cin>>N>>M>>Q>>S;
		if(N==0&&M==0&&Q==0&&S==0) break;

		vector<Node> nodes(N);
		for(int m=0;m<M;++m){
			int u,v,w;
			cin>>u>>v>>w;
			nodes[u].conn.push_back({v,w});
		}

		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push({0,S});
		while(!pq.empty()){
			auto [d,i] = pq.top();
			pq.pop();

			if(d<nodes[i].minDist){
				nodes[i].minDist=d;
				for(auto [to,w] : nodes[i].conn){
					pq.push({d+w,to});
				}
			}
		}

		for(int q=0;q<Q;++q){
			int dest;
			cin>>dest;
			if (nodes[dest].minDist == numeric_limits<int>::max()){
				cout<<"Impossible\n";
			}else{
				cout<<nodes[dest].minDist<<"\n";
			}
		}

		cout<<"\n";
	}
}