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
	int M;
	cin>>M;

	int i=1;
	int n=1;
	while(1){
		int curr = (1LL << ((n-1)/2));
		deb(curr);
		if (i+curr > M) {
			break;
		}else{
			i+=curr;
			++n;
		}
	}

	int k = M-i;
	int res = 1LL << (n-1LL);
	res += k << (n/2);

	deb(M, i, k, nmezzi, res);

	for(int j=0;j<n/2;++j){
		res |= ((res>>(n-j-1))&1)<<j;
	}

	cout<<res<<"\n";
}
