#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<typename T>struct is_iterable{template<class E>static int16_t f(...);template<class E>static int8_t f(int8_t,typename E::const_iterator=E().end());enum{value=sizeof(f<T>(0))==sizeof(int8_t)};};template<class T,typename enable_if<is_iterable<T>::value,bool>::type=false>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class... Ts>void deb(T t,Ts... args) {cout<<t<<"  ";deb(args...);}
#else
template<class...Ts>constexpr void deb(const Ts&...){}
#endif

signed main() {
	
}
