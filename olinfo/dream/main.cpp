#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	constexpr int M=666013;
	int K, X;
	in>>K>>X;

	vector<int> ps(X);
	ps[0]=1;
	for(int x=1;x<X;x++){
		ps[x]=ps[x-1]*10 % M;
	}

	int res=0, p=1;
	for(int x=0;x<X/2;++x){
		int k = K/p;
		int cycles, lastVal;
		if (x==(X/2-1)) {
			cycles = k / 9;
			lastVal = k % 9 + 1;
		} else {
			cycles = k / 10;
			lastVal = k % 10;
		}
		deb(k, cycles, lastVal, res);

		res +=
			((
				((
					// the digit will go 0,1,2...9 for `cycles` times
					(0+1+2+3+4+5+6+7+8+9)*cycles % M +
					// then it will settle *before* the last val
					(lastVal*(lastVal-1)/2) % M
				) % M) * p % M +
				(
					// the last value is repeated some more times
					lastVal*(K - k*p)
				) % M
			) % M) * (
				// this digit is both at pos `X/2-x-1` and `X/2+x`
				(ps[X/2-x-1] + ps[X/2+x]) % M
			) % M;
		res %= M;

		if (p <= K) {
			// p is not useful anymore when above K, so prevent it from overflowing
			p*=10;
		}
	}

	out<<res<<"\n";
}
