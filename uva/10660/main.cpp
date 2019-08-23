#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;
using arr = array<si, 25>;

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

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si N;
		in>>N;

		arr table;
		fill(begin(table), end(table), 0);
		auto updDist = [&](arr ar, si pos) {
			si r=pos/5, c=pos%5;
			for(int i = 0; i != 25; ++i) {
				si ri=i/5, ci=i%5;
				si dist = table[i]*(abs(r-ri)+abs(c-ci));
				if (dist<ar[i]) ar[i]=dist;
			}
			return ar;
		};

		for(int n = 0; n != N; ++n) {
			si r,c,v;
			in>>r>>c>>v;
			table[r*5 + c]=v;
		}

		si bestSumSoFar=numeric_limits<si>::max();
		si ba,bb,bc,bd,be;
		for(int a = 0; a != 21; ++a) {
			arr A;
			fill(begin(A), end(A), numeric_limits<si>::max());
			A = updDist(A, a);
			for(int b = 1; b != 22; ++b) if (b!=a) {
				arr B = updDist(A, b);
				for(int c = 2; c != 23; ++c) if (c!=b && c!=a) {
					arr C = updDist(B, c);
					for(int d = 3; d != 24; ++d) if (d!=c && d!=b && d!=a) {
						arr D = updDist(C, d);
						for(int e = 4; e != 25; ++e) if (e!=d && e!=c && e!=b && e!=a) {
							si row=e/5, col=e%5, sum=0;
							for(int i = 0; i != 25; ++i) {
								si ri=i/5, ci=i%5;
								si dist = table[i]*(abs(row-ri)+abs(col-ci));
								if (dist<D[i]) sum+=dist;
								else sum+=D[i];
							}

							if(sum<bestSumSoFar) {
								bestSumSoFar=sum;
								ba=a; bb=b; bc=c; bd=d; be=e;
							}
						}
					}
				}
			}
		}

		out<<ba<<" "<<bb<<" "<<bc<<" "<<bd<<" "<<be<<"\n";
	}
}
