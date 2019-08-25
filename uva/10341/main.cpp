#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

bool equal(flt a, flt b) {
	return abs(a-b) < 1e-12;
}

int main() {
	out<<fixed<<setprecision(4);
	while(1) {
		si p,q,r,s,t,u;
		in>>p>>q>>r>>s>>t>>u;
		if (!in) break;
		if(!(p||q||r||s||t||u)) {
			out<<"0.0000\n";
			continue;
		}

		auto f = [&](flt x) {
			return  p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x)            + t*x*x + u;
		};
		
		flt besty=1234567890,bestx;
		for(flt x=0.0L; x <= 1.0L; x += 0.01L) {
			flt y=f(x);
			if (abs(y)<abs(besty)) {
				besty=y;
				bestx=x;
			}
		}

		flt nby=1234567890, nbx;
		for(flt x=max(0.L, bestx-0.01L); x <= min(bestx+0.01, 1.L); x += 0.0001L) {
			flt y=f(x);
			if (abs(y)<abs(nby)) {
				nby=y;
				nbx=x;
			}
		}

		if (equal(nbx, 0.L) || equal(nbx, 1.L)) {
			deb("here");
			besty=nby;
			bestx=nbx;
			nby=1234567890;
			for(flt x=bestx-0.0001L; x <= bestx+0.0001; x += 0.000001L) {
				flt y=f(x);
				if (abs(y)<abs(nby)) {
					nby=y;
					nbx=x;
				}
			}
		}

		//deb(besty, bestx, "\n", nby, nbx, "\n");
		if (abs(nby) > 0.01 || nbx<-1e-15L || nbx>(1.0L+1e-15)) {
			out<<"No solution\n";
		} else {
			out<<nbx<<"\n";
		}
	}
}
