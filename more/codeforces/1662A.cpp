#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	while(T--){
		int N;
		cin>>N;
		vector<int> bty(10, -1);

		for(int n=0;n<N;++n){
			int b,d;
			cin>>b>>d;
			bty[d-1]=max(bty[d-1], b);
		}

		if (count(bty.begin(), bty.end(), -1)) {
			cout<<"MOREPROBLEMS\n";
		} else {
			cout<<accumulate(bty.begin(), bty.end(), 0)<<"\n";
		}
	}
}