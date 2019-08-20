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

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		if(t!=0) out<<"\n";
		si N;
		in>>N;
		in.ignore();

		vec<si> pcs(N);
		si val=0;
		generate(pcs.begin(), pcs.end(), [&val](){ return val++; });
		auto parent = [&pcs](si i){
			while(pcs[i]!=i) i=pcs[i];
			return i;
		};

		si succ=0,unsucc=0;
		while(1) {
			ch c=in.get();
			if(c=='\n' || (!in)) break;

			si i,j;
			in>>i>>j; i--; j--;
			in.ignore();
			deb(c,i,j);
			debc(pcs);
			deb(parent(3));

			if(c=='c') {
				pcs[parent(j)]=parent(i);
			} else if (c=='q') {
				bool successful = (parent(i)==parent(j));
				succ += successful;
				unsucc += (!successful);
			} else {
				assert(false);
			}
		}
		out<<succ<<","<<unsucc<<"\n";
	}
}
