#include <bits/stdc++.h>
using namespace std;

// (explore(conn) && explore(reversed conn)) if and only if (the graph is strongly connected)
bool explore(const vector<set<int>>& conn){
	vector<bool> seen(conn.size(),false);
	queue<int> q;
	q.push(0);
	seen[0]=true;

	while(!q.empty()){
		int i=q.front();
		q.pop();

		for(auto c:conn[i]){
			if(!seen[c]){
				seen[c]=true;
				q.push(c);
			}
		}
	}

	return all_of(seen.begin(), seen.end(), [&](bool b){return b;});
}

int main(){
	int t=1;
	while(1){
		int N,M;
		cin>>N>>M;
		if(cin.eof()) break;
		cout<<"Case "<<t<<": ";
		++t;

		vector<pair<int,int>> edges;
		vector<set<int>> conna(N),connb(N);
		for(int m=0;m<M;++m){
			int a,b;
			cin>>a>>b;
			edges.push_back({a,b});
			conna[a].insert(b);
			connb[b].insert(a);
		}

		if(explore(conna) && explore(connb)){
			cout<<"valid";
			goto testCaseEnd;
		}

		for(auto [a,b]:edges){
			conna[a].erase(b);
			conna[b].insert(a);
			connb[b].erase(a);
			connb[a].insert(b);

			if(explore(conna) && explore(connb)){
				cout<<a<<" "<<b;
				goto testCaseEnd;
			}

			conna[b].erase(a);
			conna[a].insert(b);
			connb[a].erase(b);
			connb[b].insert(a);
		}

		cout<<"invalid";
		testCaseEnd:
		cout<<"\n";
	}
}