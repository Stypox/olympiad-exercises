#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

map<string, int> scoring = {
	{"rockrock", 0},
	{"paperpaper", 0},
	{"scissorsscissors", 0},
	{"rockpaper", 1},
	{"paperrock", -1},
	{"rockscissors", -1},
	{"scissorsrock", 1},
	{"paperscissors", 1},
	{"scissorspaper", -1},
};

int main(){
	bool firstTime=true;
	while(1){
		int N,K;
		cin>>N>>K;
		if(cin.eof()) break;
		if(!firstTime){
			cout<<"\n";
		}
		firstTime=false;

		vector<int> wins(N), counts(N);
		for(int k=0;k<(K*N*(N-1)/2);++k){
			int p1,p2;
			string m1,m2;
			cin>>p1>>m1>>p2>>m2;p1--;p2--;
			if(scoring[m1+m2] == 1){
				wins[p2]++;
				counts[p1]++;
				counts[p2]++;
			} else if(scoring[m1+m2] == -1){
				wins[p1]++;
				counts[p1]++;
				counts[p2]++;
			}
		}

		for(int n=0;n<N;++n){
			if(counts[n]==0){
				cout<<"-\n";
			}else{
				printf("%.3Lf\n", (long double)wins[n]/(long double)counts[n]);
			}
		}
	}
}