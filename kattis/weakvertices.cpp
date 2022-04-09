#include <bits/stdc++.h>
using namespace std;

int main(){
	while(1){
		int N;
		cin>>N;
		if(N<0) break;

		vector<set<int>> adj(N);
		for(int a=0;a<N;++a){
			for(int b=0;b<N;++b){
				bool v;
				cin>>v;
				if(v){
					adj[a].insert(b);
				}
			}
		}

		bool first=true;
		for(int n=0;n<N;++n){
			bool inTriangle = false;
			for(int a:adj[n]){
				vector<int> inters;
				set_intersection(adj[a].begin(), adj[a].end(), adj[n].begin(), adj[n].end(), back_insert_iterator(inters));
				inTriangle |= inters.size();
			}
			if(!inTriangle){
				if (first){
					first = false;
					cout<<n;
				} else {
					cout<<" "<<n;
				}
			}
		}

		cout<<"\n";
	}
}