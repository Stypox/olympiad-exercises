#include<bits/stdc++.h>
using namespace std;

signed main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N;
		cin>>N;

		vector<pair<int,int>> pt(N);
		for(int n=0;n<N;++n){
			cin>>pt[n].first>>pt[n].second;
		}

		vector<pair<int,int>> brs(N+1);
		for(int n=0;n<N+1;++n){
			cin>>brs[n].first>>brs[n].second;
		}

		vector<int> nums(N+1), rr;
		iota(nums.begin(), nums.end(), 0);
		do {
			vector<bool> usedBrs(N+1);
			vector<int> usedPtl(N);
			for(int n=0;n<N;++n){
				double bestDist=1e12;
				int bestIdx;
				for(int m=0;m<N+1;++m){
					double dist = hypot(pt[n].first-brs[m].first, pt[n].second-brs[m].second);
					if(!usedBrs[m] && (dist<bestDist || (dist==bestDist && bestIdx==0))) {
						bestDist=dist;
						bestIdx=m;
					}
				}

				if(bestIdx==0){
					goto cont;
				} else {
					usedBrs[bestIdx]=true;
					usedPtl[n]=bestIdx;
				}
			}

			rr=usedPtl;

			cont:
			continue;
		} while (next_permutation(nums.begin(), nums.end()));

		if(rr.size()) {
			cout<<"Case #"<<t+1<<": POSSIBLE"<<endl;
			for(int n=0;n<N;++n){
				cout<<n+1<<" "<<rr[n]+1<<"\n";
			}
		} else {
			cout<<"Case #"<<t+1<<": IMPOSSIBLE"<<endl;
		}
	}
}