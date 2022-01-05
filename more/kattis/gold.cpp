#include <bits/stdc++.h>
using namespace std;

int main(){
	int W,H;
	cin>>W>>H;

	int ph, pw;
	vector<string> map(H);
	for(int h=0;h<H;++h){
		cin>>map[h];
		for(int w=0;w<W;++w){
			if(map[h][w]=='P'){
				ph=h;
				pw=w;
				map[h][w]='.';
			}
		}
	}

	vector<vector<bool>> visited(H, vector<bool>(W, false));
	function<int(int, int)> dfs = [&](int h, int w) -> int {
		if (visited[h][w] || map[h][w]=='#') return 0;
		visited[h][w] = true;
		int res = map[h][w]=='G';

		for(auto [dh,dw] : initializer_list{pair{1,0}, {-1,0}, {0,1}, {0,-1}}) {
			if (map[h+dh][w+dw]=='T') return res;
		}

		for(auto [dh,dw] : initializer_list{pair{1,0}, {-1,0}, {0,1}, {0,-1}}) {
			res += dfs(h+dh, w+dw);
		}

		return res;
	};

	cout<<dfs(ph, pw)<<"\n";
}