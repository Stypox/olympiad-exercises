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

constexpr si lsOne(si i) {
	return i & (-i);
}

struct FT {
	vec<si> data;
	FT(si N) : data(N+1) {}

	si get(si i) {
		si sum=0;
		for(; i!=0; i-=lsOne(i))
			sum+=data[i];
		return sum;
	}

	si get(si a, si b) {
		return get(b) - get(a-1);
	} 

	void set(si i, si val) {
		si delta = val - get(i,i);
		for(; i<data.size(); i+=lsOne(i))
			data[i]+=delta;
	}
};

int main() {
	while(1){
		si N,K;
		in>>N>>K;
		if(N==0 || !(in)) break;

		FT neg{N}, zero{N};
		auto setv = [&](si i, si v){
			neg.set(i, v<0);
			zero.set(i, v==0);
		};
		auto getv = [&](si a, si b) {
			si n=neg.get(a,b), z=zero.get(a,b);
			if (z!=0)     return '0';
			else if (n%2) return '-';
			else          return '+';
		};

		for(int n = 1; n <= N; ++n) {
			si v;
			in>>v;
			setv(n,v);
		}

		for(int k = 0; k != K; ++k) {
			ch c;
			in>>c;

			if(c=='C') {
				si i,v;
				in>>i>>v;
				setv(i,v);
			} else if(c=='P') {
				si a,b;
				in>>a>>b;
				out<<getv(a,b);
			} else {
				assert(false);
			}
		}

		out<<"\n";
	}
}
