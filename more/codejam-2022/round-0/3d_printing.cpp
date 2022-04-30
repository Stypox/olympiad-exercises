#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int a1,b1,c1,d1;
		int a2,b2,c2,d2;
		int a3,b3,c3,d3;

		cin>>a1>>b1>>c1>>d1;
		cin>>a2>>b2>>c2>>d2;
		cin>>a3>>b3>>c3>>d3;

		int mins[4] {
			min({a1,a2,a3}),
			min({b1,b2,b3}),
			min({c1,c2,c3}),
			min({d1,d2,d3})
		};

		int sum=0;
		int result[4] { 0,0,0,0 };
		for(int i=0;i<4;++i){
			result[i]=min(1'000'000 - sum, mins[i]);
			sum+=result[i];
		}

		cout<<"Case #"<<t+1<<": ";
		if (sum==1'000'000){
			for(int i=0;i<4;++i){
				cout<<" "<<result[i];
			}
		} else {
			cout<<" IMPOSSIBLE";
		}
		cout<<"\n";
	}
}
