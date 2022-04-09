#include <bits/stdc++.h>
using namespace std;

int main() {
	array<array<bool,8>,8> cb;
	vector<pair<int, int>> qs;
	for (int i=0;i<8;++i){
		for (int j=0;j<8;++j){
			char c;
			cin>>c;
			cb[i][j]=(c=='*');
			if(c=='*') qs.push_back({i,j});
		}
		cin.ignore();
	}

	if (qs.size() != 8){
		cout<<"invalid\n";
		return 0;
	}

	for(auto [i,j] : qs){
		for (int x=0;x<8;++x){
			for(int y=0;y<8;++y){
				if ((x!=i || y!=j) && (x==i || y==j || (x-i)==(y-j) || (x-i)==-(y-j)) && cb[x][y]) {
					cout<<"invalid\n";
					return 0;
				}
			}
		}
	}
	cout<<"valid\n";
}