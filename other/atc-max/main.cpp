#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

enum From { horizontal=0, vertical=1 };
struct Data {
	si x, y;
	From from;
	si turns;
	vec<pair<si, si>> path;

	Data(si x, si y, From from, si turns, vec<pair<si, si>> path) :
		x{x}, y{y}, from{from}, turns{turns}, path{path} {}
};
struct Node {
	si x, y;
	From from;
	si turns = -1;
	vec<pair<si, si>> path;

	void set(si x_, si y_, From from_) {
		x = x_;
		y = y_;
		from = from_;
	}
	void setStarting() {
		turns = 0;
	}
	void printPath() {
		for(auto&& p : path) {
			cout<<"("<<p.first<<","<<p.second<<") ";
		}
	}
	void print() {
	#ifdef DEBUG
		cout<<"Node at ("<<x<<","<<y<<"), from "<<(from==horizontal ? "horizontal" : "vertical")<<". Path:\n";
		printPath();
		cout<<"\n";
	#endif
	}
};

bool isInPath(vec<pair<si, si>> path, si x, si y) {
	return find(path.begin(), path.end(), pair{x, y}) != path.end();
}

struct Map {
	vec<vec<array<Node, 2>>> squares;
	si goal;

	queue<Data> q;

	Map(si N) :
		squares(N, vec<array<Node, 2>>(N)), goal{N-1}, q{} {
		for(si x = 0; x != N; ++x) {
			for(si y = 0; y != N; ++y) {
				squares[x][y][horizontal].set(x, y, horizontal);
				squares[x][y][vertical].set(x, y, vertical);
			}
		}
	}
	
	void printLongestPath() {
		q.push(Data{0,0,horizontal,0,{}});
		q.push(Data{0,0,vertical,0,{}});

		while(!q.empty()) {
			auto [x, y, from, turns, path] = q.front();
			q.pop();
			deb("Visiting x,y=", x, y, "from=", from);

			if(turns > squares[x][y][from].turns || path.size() < squares[x][y][from].path.size()) {
				if(isInPath(path, x, y)) continue;

				squares[x][y][from].turns = turns;
				squares[x][y][from].path = path;

				si turnsHorizontal = (from==vertical) + turns,
					turnsVertical = (from==horizontal) + turns;
				
				path.push_back({x,y});
				// move horizontally
				if(x!=0) {
					q.push(Data{x-1,y,horizontal,turnsHorizontal,path});
					deb("Adding horizontal", x-1, y, "turns", turnsHorizontal);
				}
				if(x!=goal) {
					q.push(Data{x+1,y,horizontal,turnsHorizontal,path});
					deb("Adding horizontal", x+1, y, "turns", turnsHorizontal);
				}

				// move vertically
				if(y!=0) {
					q.push(Data{x,y-1,vertical,turnsVertical,path});
					deb("Adding vertical", x, y-1, "turns", turnsVertical);
				}
				if(y!=goal) {
					q.push(Data{x,y+1,vertical,turnsVertical,path});
					deb("Adding vertical", x, y+1, "turns", turnsVertical);
				}
			}
		}

		squares[goal][goal][horizontal].print();
		squares[goal][goal][vertical].print();
		
		// subtracting one since the start is not a turn
		if (squares[goal][goal][horizontal].turns > squares[goal][goal][vertical].turns) {
			cout<<"LONGEST PATH FOR N="<<goal+1<<" is "<<squares[goal][goal][horizontal].turns-1<<" -- ";
			squares[goal][goal][horizontal].printPath();
			cout<<"\n\n";
		}
		else {
			cout<<"LONGEST PATH FOR N="<<goal+1<<" is "<<squares[goal][goal][vertical].turns-1<<" -- ";
			squares[goal][goal][vertical].printPath();
			cout<<"\n\n";
		}
	}

	void print() {
		for(int y = 0; y <= goal; ++y) {
			for(int x = 0; x <= goal; ++x) {
				//deb("x,y", x, y, ": visited x,y", squares[x][y][horizontal], squares[x][y][vertical]);
			}
		}
	}
};

int main() {
	si N=1;
	while(1) {
		Map m{N};
		m.printLongestPath();
		++N;
	}
}