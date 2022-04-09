#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	while (1) {
		int N,B;
		cin>>N>>B;
		if (N==-1) break;

		vector<int> A(N);
		for (int n=0;n<N;++n){
			cin>>A[n];
		}

		auto possible = [&](int ppb) {
			int b=B;
			for (int n=0;n<N;++n){
				b-=(A[n] / ppb + (A[n] % ppb == 0 ? 0 : 1));
				if (b<0) return false;
			}
			return true;
		};

		int a=0, b=5000001;
		while(true){
			int m=(a+b)/2;
			if (m==a) break;

			if (possible(m)) {
				b=m;
			} else {
				a=m;
			}
		}

		cout<<a+1<<"\n";
	}
}