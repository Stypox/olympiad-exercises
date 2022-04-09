#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int N;
	cin>>N;

	function<int(int,int,int)> rec = [&](int n, int x, int y) -> int {
		if (n==1) {
			return 1;
		} else if (x >= n/2 && y >= n/2) {
			return -rec(n/2, x-n/2, y-n/2);
		} else {
			return rec(n/2, x%(n/2), y%(n/2));
		}
	};

	for (int i=0;i<N;++i){
		int n,x,y,w,h;
		cin>>n>>x>>y>>w>>h;

		for(int i=0;i<h;++i){
			for(int j=0;j<w;++j){
				if (j!=0)cout<<" ";
				cout<<rec(n, x+j, y+i);
			}
			cout<<"\n";
		}
		cout<<"\n";
	}
}