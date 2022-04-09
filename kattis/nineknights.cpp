#include <bits/stdc++.h>
using namespace std;

int main(){
	array<bitset<5>, 5> board;
	int count=0;
	for(int i=0;i<5;++i){
		for(int j=0;j<5;++j){
			char c;
			cin>>c;
			count += (c=='k');
			board[i][j] = (c=='k');
		}
		cin.ignore();
	}

	auto knightAt = [&](int i, int j) -> bool {
		if (i<0||i>=5||j<0||j>=5)return false;
		return board[i][j];
	};

	bool valid=(count==9);
	for(int i=0;i<5;++i){
		for(int j=0;j<5;++j){
			if (knightAt(i,j) && (knightAt(i-1,j-2) || knightAt(i-2,j-1) || knightAt(i+1,j+2) || knightAt(i+2,j+1)
			                   || knightAt(i+1,j-2) || knightAt(i+2,j-1) || knightAt(i-1,j+2) || knightAt(i-2,j+1))) {
				valid=false;
			}
		}
	}

	cout<<(valid?"valid\n":"invalid\n");
}