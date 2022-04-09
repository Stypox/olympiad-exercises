#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int N;
	cin>>N;

	vector<int> A(N),B(N);
	for (int n=0;n<N;++n) cin>>A[n];
	for (int n=0;n<N;++n) cin>>B[n];

	int aSum[3] {0, 0, 0};
	for(int n=0;n<N;++n){
		aSum[n % 3] += A[n];
	}

	int res[3] {0, 0, 0};
	for(int n=0;n<N;++n){
		res[n % 3] += B[n] * aSum[n % 3];
		res[(n+1) % 3] += B[n] * aSum[(n+2) % 3];
		res[(n+2) % 3] += B[n] * aSum[(n+1) % 3];
	}

	cout<<res[2]<<" "<<res[1]<<" "<<res[0]<<"\n";
}