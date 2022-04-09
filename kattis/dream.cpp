#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;

	stack<string> events;
	map<string, int> times;
	for (int n=0;n<N;++n){
		string s;
		cin>>s;

		if(s=="E"){
			cin>>s;
			times[s] = events.size();
			events.push(s);
		} else if(s=="D"){
			int r;
			cin>>r;
			for(int i=0;i<r;++i){
				times.erase(events.top());
				events.pop();
			}
		} else {
			assert(s=="S");
			int K;
			cin>>K;

			int maxYes=-1, minNot=events.size();
			bool impossible=false;
			for(int k=0;k<K;++k){
				cin>>s;
				if(s[0] == '!'){
					s=s.substr(1);
					if(times.count(s)){
						minNot=min(minNot, times[s]);
					}
				} else {
					if(times.count(s)){
						maxYes=max(maxYes, times[s]);
					} else {
						impossible=true;
					}
				}
			}

			if (impossible || minNot <= maxYes) {
				cout<<"Plot Error\n";
			} else if (minNot==events.size()) {
				cout<<"Yes\n";
			} else {
				cout<<events.size()-minNot<<" Just A Dream\n";
			}
		}
	}
}
