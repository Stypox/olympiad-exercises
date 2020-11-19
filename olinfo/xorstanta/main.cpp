#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

int32_t main() {
	int T;
	in>>T;
	for (int t=0;t<T;++t){
		int N;
		in>>N;

		int xa=0;
		int numcifre=0;
		for (int i=1;i<=N;i<<=1) {
			xa^=i;
			numcifre++;
		}

		int xb=0;
		for (int i=0;i<numcifre;++i){
			int s=1<<i;
			int k=1<<(i+1);
			int r=((N+1)%k);

			if (r>s && ((r-s)%2==1)) {
				xb^=s;
			}
		}
		xb|=1;
		xb^=!(((N+1)%4) >= 2);
		xb^=xa;

		out<<xa+xb<<"\n";
	}
}
