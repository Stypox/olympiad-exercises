#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	while(T--){
		int N,M;
		cin>>N>>M;

		int maxr=0,maxw=0;
		for(int m=0;m<M;++m){
			int r,w;
			cin>>r>>w;
			maxr=max(maxr,r);
			maxw=max(maxw,w);
		}

		if(maxr+maxw <= N) {
			cout<<string(maxr, 'R')<<string(N-maxr, 'W')<<"\n";
		} else {
			cout<<"IMPOSSIBLE\n";
		}
	}
}