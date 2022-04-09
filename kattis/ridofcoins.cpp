#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int P;
	cin>>P;

	int n1, n5, n10, n25;
	cin>>n1>>n5>>n10>>n25;

	/*for(int i4=0;i4<n25;++i4){
		for(int i10=0;i10<n10;++i10){
			for(int i5=0;i5<n5;++i5){
				for(int i1=0;i1<n1;++i1){

				}
			}
		}
	}*/

	for(int i1=min(n1,P);i1>=0;--i1){
		if ((P-i1-n5*5-n10*10)/25 > n25) continue;
		for(int i5=min(n5,(P-i1)/5+1);i5>=0;--i5){
			if ((P-i1-i5*5-n10*10)/25 > n25) continue;
			for(int i10=min(n10,(P-i1-i5*5)/10+1);i10>=0;--i10){
				int p=P-i1-i5*5-i10*10;
				if (p >= 0 && (p%25)==0) {
					if (p/25 > n25) {
						cout<<"Impossible\n";
						return 0;
					}
					cout<<i1+i5+i10+(p/25)<<"\n";
					return 0;
				}
			}
		}
	}
	cout<<"Impossible\n";
}
