#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;

	vector<int> A(N),B(N),T(N);
	for(int n=0;n<N;++n){
		cin>>A[n]>>B[n]>>T[n];
	}

	vector<vector<int>> mem(N, vector<int>(25001, -1));
	function<int(int,int)> rec = [&](int n, int t) -> int {
		if(n>=N) return 0;
		assert(t>=0);
		if(mem[n][t] != -1) return mem[n][t];

		int result = rec(n+1, t);
		if (B[n] == 0) {
			if (A[n] != 0 && t-T[n]>=0) {
				result = max(result, A[n] + rec(n, t-T[n]));
			}
		} else {
			int totFunHere = 0;
			for(int k=0;k<t/T[n];++k){
				int currFunHere = A[n] - k*k*B[n];
				if (currFunHere < 0) break;
				totFunHere += currFunHere;
				result = max(result, totFunHere + rec(n+1, t-T[n]*(k+1)));
			}
		}

		return mem[n][t] = result;
	};

	int Q;
	cin>>Q;
	for(int q=0;q<Q;++q){
		int t;
		cin>>t;
		cout<<rec(0,t)<<"\n";
	}
}