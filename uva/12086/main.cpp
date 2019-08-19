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

class FenwickTree {
	// least significant one bit
	static constexpr si lsOne(si x) { return x & (-x); }
	vec<si> data;

	si query(si b) {
		si sum=0;
		for(; b!=0; b-=lsOne(b))
			sum += data[b];
		return sum;
	}

public:
	FenwickTree(si N) : data(N+1, 0) {}
	si query(si a, si b) { return query(b) - query(a-1); }
	void adjust(si i, si delta) { for(; i<data.size(); i+=lsOne(i)) data[i] += delta; }
	void set(si i, si value) { adjust(i, value - query(i,i)); }
	void deb() { debc(data, "FenwickTree data: "); }
};

int main() {
	si t=0;
	while(1){
		si N;
		in>>N;
		if(N==0) break;

		if(t!=0) out<<"\n";
		++t;
		out<<"Case "<<t<<":\n";

		FenwickTree ft{N};
		for(int n = 0; n != N; ++n) {
			si r;
			in>>r;
			ft.set(n+1, r);
		}
		ft.deb();
		
		while(1) {
			ch action;
			in>>action;

			if(action=='S'){
				si x,r;
				in>>x>>r;
				ft.set(x,r);
				deb("Set",x,"to",r);
			} else if(action=='M'){
				si x,y;
				in>>x>>y;
				out<<ft.query(x,y)<<"\n";
				deb("Query",x,y);
			} else {
				str tmp;
				in>>tmp;
				break;
			}
			ft.deb();
		}
		deb();
	}
}
