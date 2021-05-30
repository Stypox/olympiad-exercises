#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

istream& in = cin;
ostream& out = cout;
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Point {
   int x,y;
};

istream& operator>>(istream& i, Point&p) { i>>p.x>>p.y; return i; }
int operator^(const Point&a, const Point&b) { return a.x*b.y - a.y*b.x; }

signed main() {
	int N;
	in>>N;

   int A=0;
	Point first;
	in>>first;
	Point last=first;
	for(int n=1;n<N;++n){
      Point p;
      in>>p;
      A+=last^p;
      last=p;
	}
	A+=last^first;

	out<<abs(A)<<"\n";
}
