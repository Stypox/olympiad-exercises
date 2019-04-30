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
	si x, y, turns;
	From from;

	Data(si x, si y, From from, si turns) :
		x{x}, y{y}, turns{turns}, from{from} {}
};

auto sqless = [](const Data& s1, const Data& s2) {
	return s1.turns > s2.turns;
};

struct Map {
	vec<vec<array<bool, 2>>> squares;
	si goal;

	priority_queue<Data, std::vector<Data>, decltype(sqless)> q;

	Map(si N) :
		squares(N, vec<array<bool, 2>>(N)), goal{N-1}, q{sqless} {}
	
	si search() {
		q.push(Data{0,0,horizontal,0});
		q.push(Data{0,0,vertical,0});

		while(!q.empty()) {
			Data d = q.top();
			q.pop();
			deb("Visiting x,y=", d.x, d.y, "turns=", d.turns, "from=", d.from);


			if(squares[d.x][d.y][d.from])
				continue;
			else
				squares[d.x][d.y][d.from] = true;
			if(d.x == goal && d.y == goal)
				return d.turns;
			

			int turnsHorizontal = (d.from==vertical) + d.turns,
				turnsVertical = (d.from==horizontal) + d.turns;

			deb("Turns h,v", turnsHorizontal, turnsVertical);


			// move horizontally
			if(d.x!=0) {
				q.push(Data{d.x-1,d.y,horizontal,turnsHorizontal});
				deb("Adding horizontal", d.x-1, d.y, "turns", turnsHorizontal);
			}
			if(d.x!=goal) {
				q.push(Data{d.x+1,d.y,horizontal,turnsHorizontal});
				deb("Adding horizontal", d.x+1, d.y, "turns", turnsHorizontal);
			}

			// move vertically
			if(d.y!=0) {
				q.push(Data{d.x,d.y-1,vertical,turnsVertical});
				deb("Adding vertical", d.x, d.y-1, "turns", turnsVertical);
			}
			if(d.y!=goal) {
				q.push(Data{d.x,d.y+1,vertical,turnsVertical});
				deb("Adding vertical", d.x, d.y+1, "turns", turnsVertical);
			}
		}

		return -1;
	}

	void print() {
		for(int y = 0; y <= goal; ++y) {
			for(int x = 0; x <= goal; ++x) {
				deb("x,y", x, y, ": visited x,y", squares[x][y][horizontal], squares[x][y][vertical]);
			}
		}
	}
};

int main() {
	si N;
	in>>N;

	Map m{N};
	for(int x = 0; x != N; ++x) {
		for(int y = 0; y != N; ++y) {
			char ch;
			in>>ch;
			if(ch=='#') {
				// as if it has already been visited
				m.squares[x][y][horizontal] = true;
				m.squares[x][y][vertical] = true;
			}
		}
	}

	out<<m.search();

	m.print();
}