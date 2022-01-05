#include <bits/stdc++.h>
using namespace std;


int main(){
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int N;
		cin>>N;

		vector<int> nums(N);
		for(int n=0;n<N;++n){
			cin>>nums[n];
		}

		cout<<"Case #"<<t+1<<":\n";
		auto printMask = [&](int mask) {
			bool first=true;
			for(int n=0;n<N;++n){
				if(mask & (1<<n)) {
					if (!first) cout<<" ";
					first=false;
					cout<<nums[n];
				}
			}
			cout<<"\n";
		};

		unordered_map<int, int> reached;
		function<bool(int, int, int)> rec = [&](int n, int sum, int mask) {
			if(n==N) {
				if (reached.count(sum)) {
					printMask(mask);
					printMask(reached[sum]);
					return true;
				}
				reached[sum] = mask;
				return false;
			}

			return rec(n+1, sum, mask) || rec(n+1, sum+nums[n], mask | (1<<n));
		};

		if(!rec(0, 0, 0)) {
			cout<<"Impossible\n";
		}
	}
}