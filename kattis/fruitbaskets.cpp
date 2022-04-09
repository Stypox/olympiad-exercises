#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int N;
	cin>>N;

	vector<int> v(N);
	for(int n=0;n<N;++n){
		cin>>v[n];
	}

	vector<int> mem(N,0);
	for(int n=0;n<N;++n){
		for(int i=n;i<N;++i){
			mem[n]+=v[i]*(1LL<<(N-n-1LL));
		}
		//cout<<n<<" "<<mem[n]<<"\n";
	}

	function<int(int,int)> rec = [&](int i, int tot) -> int {
		if (i>=N) {
			return tot>=200?tot:0;
		} else if (tot >= 200) {
			return mem[i] + tot*(1LL<<(N-i));
		} else {
			return rec(i+1, tot) + rec(i+1, tot+v[i]);
		}
	};

	cout<<rec(0,0)<<"\n";
}