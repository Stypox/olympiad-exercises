#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;

	map<string, int> si;
	map<int, string> is;
	int curr=0;
	auto sti = [&](string& s){
		if (!si.count(s)) {
			//cout<<s<<"\n";
			//assert(curr<N);
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

	vector<vector<int>> conn(N*N*2);
	for(int n=0;n<N;++n){
		string sa;
		cin>>sa;
		int ia=sti(sa);

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
				conn[ia].push_back(ib);
				conn[ib].push_back(ia);
			}
		}
	}

	/*for(int n=0;n<N;++n){
		cout<<n<<"   ";
		for(auto e:conn[n]){
			cout<<e<<" ";
		}
		cout<<"\n";
	}*/

	string sfrom, sto;
	cin>>sfrom>>sto;
	int ifrom=sti(sfrom), ito=sti(sto);

	vector<bool> vis(N*N*2,false);
	function<bool(int)> dfs = [&](int i)->bool{
		if(i==ifrom){
			cout<<its(i);
			return true;
		} else if (vis[i]){
			return false;
		}
		vis[i]=true;

		for(int c:conn[i]){
			if(dfs(c)) {
				cout<<" "<<its(i);
				return true;
			}
		}
		return false;
	};

	if (!dfs(ito)){
		cout<<"no route found";
	}
	cout<<"\n";
}