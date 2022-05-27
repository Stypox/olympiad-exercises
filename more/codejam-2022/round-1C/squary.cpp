#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N,K;
		cin>>N>>K;

		vector<int> E(N);
		int esum=0, esquaresum=0;
		for(int n=0;n<N;++n){
			cin>>E[n];
			esum+=E[n];
			esquaresum+=E[n]*E[n];
		}

		vector<int> res;
		if (esum == 0) {
			if (esquaresum == 0) {
				res.push_back(1);
			}
		} else {
			int numerator = esquaresum - esum * esum;
			int denominator = 2 * esum;
			if (numerator % denominator == 0) {
				res.push_back(numerator / denominator);
			} else if (K != 1) {
				res.push_back(1 - esum);
				assert((esquaresum + (1 - esum) * (1 - esum) - 1) % 2 == 0);
				res.push_back((esquaresum + (1 - esum) * (1 - esum) - 1) / 2);
			}
		}

		cout << "Case #" << t+1 << ":";
		if (res.size() > 0) {
			for (auto r : res) {
				cout << " " << r;
			}
		} else {
			cout << " IMPOSSIBLE";
		}
		cout << "\n";
	}
}