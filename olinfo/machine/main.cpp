#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif




int main() {
	si C,D,Y;
	in>>C>>D>>Y;

	vector<si> M(D),P(D);
	for(auto&& m : M)
		in>>m;
	for(auto&& p : P)
		in>>p;

	vec<si> macchine(D);
	macchine[0] = C+M[0]-P[0];
	for(si d=1;d<D;++d){
		macchine[d] = macchine[d-1] + P[d-1] + M[d] - P[d];
	}

	vec<si> c(Y);
	vec<vec<si>> m(Y, vec<si>(D, numeric_limits<si>::max())), dl(Y, vec<si>(D+1, numeric_limits<si>::max()));
	for(si l=0;l<Y;++l){
		si cmin=numeric_limits<si>::max();
		for(si d=0;d<D;++d) {
			if (l-d <= 0) {
				m[l][d] = macchine[d];
				cmin = min(cmin, m[l][d]);
				break;
			}

			m[l][d] = macchine[d] + c[l-d-1];
			cmin = min(cmin, m[l][d]);
		}

		c[l] = cmin;

		if (l!=0) {
			dl[l-1][0] = cmin - c[l-1];
			for(si d=0;d<D;++d){
				if(m[l-1][d] == numeric_limits<si>::max()) break;
				dl[l-1][d+1] = m[l][d] - m[l-1][d];
			}	
		}
	}

	for(si d=0;d<D;++d) cout<<macchine[d]<<" "; cout<<"\n";

	cout<<" l  c   "<<setw(3*D)<<left<<"memoria"<<"   "<<setw(3*D)<<"differenza linee"<<"\n"<<right;
	for(si l=0;l<Y;++l){
		cout<<setw(2)<<l+1<<" "<<setw(2)<<c[l]<<"   ";

		for(si d=0;d<D;++d) {
			if (m[l][d] == numeric_limits<si>::max()) {
				cout<<"   ";
			} else {
				cout<<setw(2)<<m[l][d]<<" ";
			}
		}
		cout<<"   ";

		for(si d=0;d<=D;++d) {
			if (dl[l][d] == numeric_limits<si>::max()) {
				cout<<"   ";
			} else {
				cout<<setw(2)<<dl[l][d]<<" ";
			}
		}
		cout<<"\n";
	}
}
