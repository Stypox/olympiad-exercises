#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
constexpr int UNVISITED = -1;
constexpr int POSSIBLE = 0;
constexpr int IMPOSSIBLE = 1;
constexpr int AMBIGUOUS = 2;

int main(){
	int N;
	cin>>N;

	vector<int> C(N);
	for(int n=0;n<N;++n){
		cin>>C[n];
	}

	vector<vector<pii>> mem(N, vector<pii>(30001, {-1,0}));
	function<int(int,int)> rec = [&](int n, int s) -> int {
		if(n>=N) return s==0 ? POSSIBLE : IMPOSSIBLE;
		if(s<0) return IMPOSSIBLE;
		if(mem[n][s].first != UNVISITED) return mem[n][s].first;

		int possibility=IMPOSSIBLE, count=0;
		for(int i=0;i<(s/C[n]+1);++i){
			switch (rec(n+1, s-C[n]*i)) {
				case POSSIBLE:
					if (possibility == POSSIBLE) possibility = AMBIGUOUS;
					else possibility = POSSIBLE;
					count = i;
					break;
				case AMBIGUOUS:
					possibility = AMBIGUOUS;
					break;
			}
			if (possibility == AMBIGUOUS) {
				break;
			}
		}

		mem[n][s] = {possibility, count};
		return possibility;
	};


	int M;
	cin>>M;
	for(int m=0;m<M;++m){
		int S;
		cin>>S;
		switch (rec(0, S)) {
			case POSSIBLE:{
				int s=S;
				bool firstTime=true;
				for(int n=0;n<N;++n){
					for(int t=0;t<mem[n][s].second;++t){
						if(!firstTime) cout<<" ";
						firstTime=false;
						cout<<n+1;
					}
					s-=C[n]*mem[n][s].second;
				}
				assert(s==0);
				cout<<"\n";
				break;}
			case AMBIGUOUS:
				cout<<"Ambiguous\n";
				break;
			default:
				cout<<"Impossible\n";
				break;
		}
	}
}