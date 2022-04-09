#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 10000;
constexpr const char* S = "welcome to code jam";

int main(){
	int N;
	cin>>N;
	cin.ignore();

	for(int n=0;n<N;++n){
		string v;
		getline(cin, v);

		vector<vector<int>> mem(v.size(), vector<int>(19, -1));
		function<int(int,int)> rec = [&](int i, int s) {
			if(i<v.size()&&s<19&&mem[i][s]!=-1){
				return mem[i][s];
			}

			if(s==19){
				return 1;
			}else if(i<v.size()){
				if (v[i] == S[s]) {
					return mem[i][s] = ((rec(i+1,s) + rec(i+1,s+1)) % MOD);
				}
				return mem[i][s] = (rec(i+1,s) % MOD);
			}
			return 0;
		};

		cout<<"Case #"<<n+1<<": "<<setfill('0')<<setw(4)<<rec(0,0)<<"\n";
	}
}