#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

int main() {
	while(1) {
		si N;
		in>>N;
		if(!in) break;

		vec<vec<si>> table(N, vec<si>(N));
		vec<vec<si>> sums(N, vec<si>(N));
		for(auto&& row : table) {
			for(auto&& col : row) {
				in>>col;
			}
		}

		queue<pair<si,si>> coords;
		sums[0][0] = table[0][0];
		coords.push({0,1});
		coords.push({1,0});
		
		while(!coords.empty()) {
			pair<si,si> c = coords.front();
			coords.pop();

			if (c.first < N && c.second < N) {
				if (c.first == 0) {
					sums[c.first][c.second] = table[c.first][c.second] + sums[c.first][c.second-1];
				} else if (c.second == 0) {
					sums[c.first][c.second] = table[c.first][c.second] + sums[c.first-1][c.second];
					coords.push({c.first+1, c.second});
				} else {
					sums[c.first][c.second] = table[c.first][c.second] + sums[c.first][c.second-1]
						+ sums[c.first-1][c.second] - sums[c.first-1][c.second-1];
				}
				
				coords.push({c.first, c.second+1});
			}
		}

	#ifndef ONLINE_JUDGE
		for(auto&& row : table) {
			for(auto&& col : row) {
				cout<<col<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
		for(auto&& row : sums) {
			for(auto&& col : row) {
				cout<<col<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
	#endif

		si maxsum=numeric_limits<si>::min();
		si bx1,bx2,by1,by2;
		for(int x1 = 0;  x1 != N; ++x1)
		for(int x2 = x1; x2 != N; ++x2)
		for(int y1 = 0;  y1 != N; ++y1)
		for(int y2 = y1; y2 != N; ++y2) {
			si sum = sums[x2][y2];

			if (x1==0) {
				if (y1!=0)
					sum -= sums[x2][y1-1];
			} else if (y1==0) {
				sum -= sums[x1-1][y2];
			} else {
				sum = sum - sums[x2][y1-1] - sums[x1-1][y2] + sums[x1-1][y1-1];
			}

			if (sum>maxsum) {
				maxsum=sum;
				bx1=x1;
				bx2=x2;
				by1=y1;
				by2=y2;
			}
		}

		deb(bx1,by1,bx2,by2,maxsum,"\n\n");
		out<<maxsum<<"\n";
	}
}
