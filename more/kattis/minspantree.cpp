#include <bits/stdc++.h>
using namespace std;

struct Con{
	int a,b,w;
	bool operator<(const Con& o){
		return w<o.w;
	}
};

struct Node{
	int par=-1,rank=1;
};

int main(){
	while(1){
		int N,M;
		cin>>N>>M;
		if(N==0&&M==0)break;

		vector<Con> cons;
		for(int m=0;m<M;++m){
			int a,b,w;
			cin>>a>>b>>w;
			cons.push_back({min(a,b),max(a,b),w});
		}

		vector<Node> nodes(N);
		function<int(int)> parent = [&](int i){
			if (nodes[i].par==-1) return i;
			return parent(nodes[i].par);
		};
		auto merge = [&](int a, int b){
			a=parent(a);
			b=parent(b);
			if(a==b) return false;

			if(nodes[a].rank<nodes[b].rank)swap(a,b);
			nodes[b].par=a;
			nodes[a].rank=max(nodes[a].rank, nodes[b].rank+1);
			return true;
		};

		sort(cons.begin(), cons.end());
		int totw=0;
		vector<pair<int,int>> usedEdges;
		for(auto [a,b,w] : cons){
			if(merge(a,b)){
				totw+=w;
				usedEdges.push_back({a,b});
			}
		}

		if(usedEdges.size()!=N-1){
			cout<<"Impossible\n";
		}else{
			cout<<totw<<"\n";
			sort(usedEdges.begin(),usedEdges.end());
			for(auto [a,b]:usedEdges){
				cout<<a<<" "<<b<<"\n";
			}
		}
	}
}