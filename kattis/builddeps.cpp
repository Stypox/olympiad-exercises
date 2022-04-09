#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;

	map<string, int> si;
	map<int, string> is;
	int curr=0;
	auto sti = [&](const string& s){
		if (!si.count(s)) {
			//cout<<s<<"\n";
			assert(curr<N);
			si[s] = curr;
			is[curr] = s;
			curr++;
		}
		return si[s];
	};
	auto its = [&](int i){
		assert(is.count(i));
		return is[i];
	};

	vector<vector<int>> conn(N); // nodes that depend on node n
	vector<int> deg(N); // # of dependencies of node n
	for(int n=0;n<N;++n){
		string sa;
		cin>>sa;
		int ia=sti(sa.substr(0,sa.length()-1));

		string data;
		getline(cin, data);

		while(!data.empty()){
			int pos=data.find(" ");
			string curr;

			if(pos==string::npos){
				curr=data;
				data="";
			}else{
				curr=data.substr(0, pos);
				data=data.substr(pos+1);
			}

			if(curr!=""){
				int ib=sti(curr);
				conn[ib].push_back(ia);
				deg[ia]++;
			}
		}
	}

	string smodified;
	cin>>smodified;
	int imodified=sti(smodified);

	queue<int> q;
	for(int n=0;n<N;++n){
		if(deg[n]==0&&n!=imodified) q.push(n);
	}

	while(!q.empty()){
		int i=q.front();
		q.pop();

		for(int c:conn[i]){
			--deg[c];
			if(deg[c]==0&&c!=imodified){
				q.push(c);
			}
		}
	}

	q.push(imodified);
	vector<int> files;
	files.push_back(imodified);
	while(!q.empty()){
		int i=q.front();
		q.pop();

		for(int c:conn[i]){
			--deg[c];
			if(deg[c]==0){
				q.push(c);
				files.push_back(c);
			}
		}
	}

	for(int file:files){
		cout<<its(file)<<"\n";
	}
}