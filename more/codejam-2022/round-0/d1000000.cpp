#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int D;
		cin>>D;
		vector<int> dice(D);

		for(int d=0;d<D;++d){
			cin>>dice[d];
		}
		sort(dice.begin(), dice.end());

		int curr=0;
		for(auto&& die : dice) {
			if (die > curr) {
				++curr;
			}
		}

		cout<<"Case #"<<t+1<<": "<<curr<<"\n";
	}
}
