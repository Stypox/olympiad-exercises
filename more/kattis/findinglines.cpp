#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define double long double

struct Point{
	int x,y;
};

int main(){
	int N,P;
	cin>>N>>P;

	vector<Point> pts(N);
	for (int n=0;n<N;++n){
		cin>>pts[n].x>>pts[n].y;
	}
	shuffle(pts.begin(), pts.end(), mt19937(random_device{}()));
	if (N <= 2) {
		cout<<"possible\n";
		return 0;
	}

	for (int i=0;i<min(50,N);++i){
		map<double, int> vcts;
		auto [x0, y0] = pts[i];
		for(auto [x, y] : pts) {
			int dx = x-x0;
			int dy = y-y0;
			if (dy == 0) {
				if (dx != 0) {
					vcts[numeric_limits<double>::infinity()]++;
				}
			} else if (dx == 0) {
				vcts[0]++;
			} else {
				vcts[(double)dx/(double)dy]++;
			}
		}

		for(auto [m, count] : vcts) {
			if (count+1 >= ((N*P%100==0) ? (N*P/100) : (N*P/100+1))) {
				cout<<"possible\n";
				exit(0);
			}
		}
	}
	cout<<"impossible\n";
}