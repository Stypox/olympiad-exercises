#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;
	for(int n=0;n<N;++n){
		string c1,c2;
		int y1,y2;
		cin>>c1>>y1>>c2>>y2;
		y1--;y2--;
		int x1=c1[0]-'A', x2=c2[0]-'A';

		if ((x1+y1)%2 != (x2+y2)%2){
			cout<<"Impossible\n";
			continue;
		}

		vector<pair<int,int>> moves{{x1,y1}};
		auto addmove = [&](int x, int y){
			if (pair{x,y}!=moves.end()[-1]){
				moves.push_back({x,y});
			}
		};
		if ((x1-y1) != (x2-y2)) {
			addmove((x1+y1)/2+(x1+y1)%2, (x1+y1)/2);
			addmove((x2+y2)/2+(x2+y2)%2, (x2+y2)/2);
		}
		addmove(x2,y2);

		cout<<moves.size()-1;
		for(auto [x,y]:moves){
			//cout<<"    "<<x<<" "<<y;
			cout<<" "<<(char)(x+'A')<<" "<<y+1;
		}
		cout<<"\n";
	}
}