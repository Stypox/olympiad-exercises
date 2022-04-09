#include <bits/stdc++.h>
using namespace std;
using ld=long double;

ld factors[] = {9,4,4,4,7};

int main(){
	while(1){
		ld cfat=0,ctot=0;
		while(1){
			int ccur=0, pcur=0;
			vector<pair<int,bool>> foods;
			for(int i=0;i<5;++i){
				int v; char c;
				cin>>v;
				if(!cin) {
					cin.clear();
					goto finish;
				}
				cin>>c;

				if(c=='%'){
					pcur+=v;
					foods.push_back({v,true});
				} else if (c=='g') {
					ccur+=v*factors[i];
					foods.push_back({v*factors[i],false});
				} else {
					ccur+=v;
					foods.push_back({v,false});
				}
			}

			ld pfactor = ccur/(100.0L - pcur);
			for(int i=0;i<5;++i){
				if(foods[i].second){
					ctot+=foods[i].first*pfactor;
				}else{
					ctot+=foods[i].first;
				}
			}
			if(foods[0].second){
				cfat+=foods[0].first*pfactor;
			}else{
				cfat+=foods[0].first;
			}
		}

		finish:
		if(ctot==0){
			break;
		}
		//cout<<cfat<<" "<<ctot<<"\n";
		cout<<(int)(cfat / ctot * 100.0L + 0.5L)<<"%\n";
	}
}