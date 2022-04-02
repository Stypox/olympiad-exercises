#include <bits/stdc++.h>
using namespace std;

int main(){
	#define int long long
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int N;
		cin>>N;

		vector<int> nums(N);
		for(int n=0;n<N;++n){
			string tmp;
			cin>>tmp>>nums[n];
			nums[n]--;
		}

		int badness = 0;
		sort(nums.begin(), nums.end());
		for(int i=0; i<N; ++i){
			badness += abs(nums[i] - i);
		}

		cout<<badness<<"\n";
	}
}