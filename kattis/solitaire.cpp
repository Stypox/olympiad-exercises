#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
#define TRY_MOVE_RECURSE(xb, yb, num) auto [possible##num, board##num] = tryToMove(board, x, y, xb, yb); \
	if (possible##num) { \
		pii r = rec(board##num); \
		r.second++; \
		res = min(res, r); \
	}

pair<bool, vector<string>> tryToMove(const vector<string>& board, int xa, int ya, int xb, int yb) {
	int xm = (xa+xb)/2;
	int ym = (ya+yb)/2;
	if (xb < 0 || xb >= 5 || yb < 0 || yb >= 9 || board[xb][yb] != '.' || board[xm][ym] != 'o') {
		return {false, {}};
	}
	vector<string> board2 = board;
	board2[xa][ya]='.';
	board2[xm][ym]='.';
	board2[xb][yb]='o';
	return {true, board2};
}

int main(){
	int N;
	cin>>N;

	for(int n=0;n<N;++n){
		vector<string> board(5);
		for(int i=0;i<5;++i){
			cin>>board[i];
		}

		map<vector<string>, pii> mem;
		function<pii(const vector<string>&)> rec = [&](const vector<string>& board) -> pii {
			if (mem.count(board)) return mem[board];

			pii res{0,0};
			for(int x=0;x<5;++x) for(int y=0;y<9;++y) {
				if(board[x][y] == 'o') {
					res.first++;
				}
			}

			for(int x=0;x<5;++x) for(int y=0;y<9;++y) {
				if(board[x][y] == 'o') {
					TRY_MOVE_RECURSE(x+2, y, 1)
					TRY_MOVE_RECURSE(x-2, y, 2)
					TRY_MOVE_RECURSE(x, y+2, 3)
					TRY_MOVE_RECURSE(x, y-2, 4)
				}
			}

			return mem[board] = res;
		};

		auto [pieces, moves] = rec(board);
		cout<<pieces<<" "<<moves<<"\n";
	}
}