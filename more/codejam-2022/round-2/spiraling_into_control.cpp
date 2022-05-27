#include<bits/stdc++.h>
using namespace std;

signed main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N,K;
		cin>>N>>K;

		vector<vector<int>> nums(N, vector<int>(N, -1));
		auto numsat = [&](int x, int y) -> int {
			if (x<0 || x>=N || y<0 || y>=N) return 0;
			else return nums[x][y];
		};

		pair<int,int> dir={1,0};
		for(int i=0, x=0, y=0; i<N*N; ++i) {
			nums[x][y] = i+1;
			if (dir.first==1 && numsat(x+1, y) != -1) {
				dir={0,1};
			} else if (dir.first==-1 && numsat(x-1, y) != -1) {
				dir={0,-1};
			} else if (dir.second==1 && numsat(x,y+1) != -1) {
				dir={-1,0};
			} else if (dir.second==-1 && numsat(x,y-1) != -1) {
				dir={1,0};
			}
			x+=dir.first;
			y+=dir.second;
		}

		vector<vector<vector<bool>>> seen(N, vector<vector<bool>>(N, vector<bool>(K+1, false)));
		vector<pair<int,int>> mosse;
		function<bool(int,int,int)> doable = [&](int x, int y, int k) {
			if (x == N/2 && y == N/2 && k==0) return true;
			if (k<0 || seen[x][y][k]) return false;
			seen[x][y][k] = true;

			int i=numsat(x,y);
			for (auto [xi,yi] : initializer_list{pair{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}}) {
				if (numsat(xi, yi) > i && doable(xi, yi, k-1)) {
					int ii=numsat(xi,yi);
					if (ii != i+1) {
						mosse.push_back({i, ii});
					}
					return true;
				}
			}
			return false;
		};

		if(doable(0,0,K)) {
			cout<<"Case #"<<t+1<<": "<<mosse.size()<<endl;
			for(auto it=mosse.rbegin(); it!=mosse.rend(); ++it) {
				cout<<it->first<<" "<<it->second<<endl;
			}
		} else {
			cout<<"Case #"<<t+1<<": "<<"IMPOSSIBLE"<<endl;
		}
	}
}