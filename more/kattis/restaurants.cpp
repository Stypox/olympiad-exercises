#include <bits/stdc++.h>
using namespace std;

int main(){
	while (1) {
		int N;
		cin>>N;
		if (N==0) break;

		int p1 = 0, p2 = 0;
		for(int n=0;n<N;++n){
			string s;
			int v;
			cin>>s>>v;

			if (s=="DROP"){
				p1 += v;
				cout<<"DROP 1 "<<v<<"\n";
			} else {
				assert(s=="TAKE");
				if (v>p2) {
					if (p2 != 0) {
						cout<<"TAKE 2 "<<p2<<"\n";
					}
					cout<<"MOVE 1->2 "<<p1<<"\n";
					cout<<"TAKE 2 "<<v-p2<<"\n";
					p2=p2+p1-v;
					p1=0;
				} else {
					p2 -= v;
					cout<<"TAKE 2 "<<v<<"\n";
				}
			}
		}
		cout<<"\n";
	}
}