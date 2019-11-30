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
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

struct Point {
	si x,y;
	Point operator-(const Point& other) const {return {x-other.x, y-other.y};}
	si operator*(const Point& other) const {return x*other.x+y*other.y;}
	bool operator<(const Point& other) const {return pair<si,si>{x,y} < pair<si,si>{other.x,other.y};}
};

si product(const Point&a,const Point&b,const Point&c){
	Point v = b-a;
	Point w = c-b;
	
	Point v1{-v.y, v.x};
	return v1*w;
}

bool goesRight(const Point&a,const Point&b,const Point&c){
	return product(a,b,c)<0;
}
bool goesLeft(const Point&a,const Point&b,const Point&c){
	return product(a,b,c)>0;
}

int main() {
	si N;
	in>>N;
	if (N<=3) {
		out<<N<<"\n";
		return 0;
	}

	vec<Point> points(N, Point{0,0});
	for(si n=0;n<N;++n){
		in>>points[n].x>>points[n].y;
	}

	sort(points.begin(),points.end());
	vec<si> stak1{0,1};
	for(si n=2;n<N;++n){
		while (stak1.size()>=2 && !goesRight(points[stak1.end()[-2]], points[stak1.end()[-1]], points[n]))
			stak1.pop_back();
		stak1.push_back(n);
	}

	vec<si> stak2{0,1};
	for(si n=2;n<N;++n){
		while (stak2.size()>=2 && !goesLeft(points[stak2.end()[-2]], points[stak2.end()[-1]], points[n]))
			stak2.pop_back();
		stak2.push_back(n);
	}

	out<<stak1.size() + stak2.size() - 2;
}
