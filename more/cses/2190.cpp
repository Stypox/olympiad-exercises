#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

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

ostream& operator<<(ostream&o,const Point&p) {o<<"("<<p.x<<","<<p.y<<")"; return o;}
istream& operator>>(istream&i,Point&p){i>>p.x>>p.y;return i;}
Point operator-(const Point& a, const Point& b) {return {a.x-b.x, a.y-b.y};}
Point operator+(const Point& a, const Point& b) {return {a.x+b.x, a.y+b.y};}
int operator^(const Point& a, const Point& b) {return a.x*b.y - a.y*b.x;}

int sign(int i) {
   return i==0 ? 0 : i<0 ? -1 : 1;
}

signed main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
      Point a, b, c, d;
      cin>>a>>b>>c>>d;

      int x=sign((b-a)^(c-a)), y=sign((b-a)^(d-a)), z=sign((d-c)^(a-c)), w=sign((d-c)^(b-c));

      bool yes;
      if (x==0&&y==0&&z==0&&w==0){
         if (a.x==b.x) {
            if (a.y > b.y) swap(a,b);
            if (c.y > d.y) swap(c,d);
            if (a.y > c.y) { swap(a,c); swap(b,d); }
            yes = !(c.y > b.y);
         } else {
            if (a.x > b.x) swap(a,b);
            if (c.x > d.x) swap(c,d);
            if (a.x > c.x) { swap(a,c); swap(b,d); }
            yes = !(c.x > b.x);
         }
      } else {
         yes = x*y <= 0 && z*w <= 0;
      }

      cout<<(yes?"YES\n":"NO\n");
	}
}
