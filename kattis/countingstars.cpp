#include <bits/stdc++.h>
using namespace std;

int main(){
	int T=1;
	while(true){
		int N,M;
		cin>>N>>M;
		if (cin.eof()) break;

		vector<vector<bool>> sky(N, vector<bool>(M));
		for(int n=0;n<N;++n){
			string s;
			cin >> s;
			for(int m=0;m<M;++m){
				sky[n][m] = (s[m] == '#');
			}
		}

		function<void(int, int)> bucketfill = [&](int n, int m) {
			if (n < 0 || n >= N || m < 0 || m >= M || sky[n][m]) return;
			sky[n][m] = true;
			bucketfill(n+1, m);
			bucketfill(n-1, m);
			bucketfill(n, m+1);
			bucketfill(n, m-1);
		};

		int res=0;
		for(int n=0;n<N;++n){
			for(int m=0;m<M;++m){
				res+=!sky[n][m];
				bucketfill(n, m);
			}
		}

		cout<<"Case "<<T<<": "<<res<<"\n";
		T++;
	}
}