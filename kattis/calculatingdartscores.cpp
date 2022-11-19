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
#define in cin
#define out cout

signed main() {
	int n;
	in>>n;

	auto isInvalid = [&](int a) {
		return (a>20 && a<=40 && a%2 != 0 && a%3 != 0) || (a>40 && a%3 != 0);
	};

	auto printPoints = [&](int v) {
		if (v == 0) {
			// nothing
		} else if (v % 3 == 0) {
			assert(v/3>0&&v/3<=20);
			out<<"triple "<<v/3<<"\n";
		} else if (v % 2 == 0) {
			assert(v/2>0&&v/2<=20);
			out<<"double "<<v/2<<"\n";
		} else {
			assert(v>0&&v<=20);
			out<<"single "<<v<<"\n";
		}
	};

	for(int a=1;a<=60;++a) {
		if (isInvalid(a)) continue;
		for(int b=0;b<=60;++b) {
			if (isInvalid(b)) continue;
			for(int c=0;c<=60;++c) {
				if (isInvalid(c)) continue;
				if (n == a+b+c) {
					printPoints(a);
					printPoints(b);
					printPoints(c);
					return 0;
				}
			}
		}
	}
	out<<"impossible\n";
}
