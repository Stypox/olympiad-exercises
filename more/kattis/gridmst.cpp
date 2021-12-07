#include <bits/stdc++.h>
using namespace std;

struct Point{
	int16_t x,y;
	int par=-1,rank=1;
};

struct Con{
	int i,j,d;
	bool operator<(const Con& o){
		return d<o.d;
	}
};

int main(){
	int N;
	cin>>N;

	vector<vector<int>> grid(1000, vector<int>(1000,-1));
	vector<Point> points;
	queue<pair<int,int>> q;
	for(int n=0;n<N;++n){
		int16_t x,y;
		cin>>x>>y;
		points.push_back({x,y});
		q.push({x,y});
		grid[x][y]=n;
	}
	if(points.size()==0){
		cout<<0<<"\n";
		return 0;
	}

	while(!q.empty()) {
		auto [x,y]=q.front();
		q.pop();
		int i=grid[x][y];

		for (auto [dx,dy] : initializer_list{pair{1,0}, {-1,0}, {0,1}, {0,-1}}){
			int nx=x+dx,ny=y+dy;
			if(nx<0||nx>=1000||ny<0||ny>=1000) continue;
			if(grid[nx][ny] == -1){
				grid[nx][ny]=i;
				q.push({nx,ny});
			}
		}
	}

	set<pair<int,int>> consSet;
	for(int a=0;a<1000;++a){
		for(int b=0;b<1000-1;++b){
			if(grid[a][b]!=grid[a][b+1]){
				consSet.insert({grid[a][b], grid[a][b+1]});
			}
			if(grid[b][a]!=grid[b+1][a]){
				consSet.insert({grid[b][a], grid[b+1][a]});
			}
		}
	}

	vector<Con> cons;
	for(auto [i,j] : consSet){
		cons.push_back({i,j,abs(points[i].x-points[j].x)+abs(points[i].y-points[j].y)});
	}
	sort(cons.begin(), cons.end());

	function<int(int)> par = [&](int i){
		if(points[i].par==-1)return i;
		assert(points[i].par!=i);
		return par(points[i].par);
	};
	function<bool(int,int)> merge = [&](int i, int j){
		i=par(i);
		j=par(j);
		if (i==j){
			return false;
		}

		if(points[i].rank<points[j].rank){
			swap(i,j);
		}
		points[j].par=i;
		return true;
	};

	int res=0;
	for(auto [i,j,d] : cons){
		if(merge(i,j)) res+=d;
	}

	cout<<res<<"\n";
}