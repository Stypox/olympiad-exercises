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
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#endif

void fight(si&a,si&b){
	if(a>=b){
		a-=b;
		b=0;
	} else {
		b-=a;
		a=0;
	}
}

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		if(t!=0) out<<"\n";
		si N,nG,nB;
		in>>N>>nG>>nB;

		multiset<si, greater<si>> G;
		for(si g = 0; g != nG; ++g) {
			si s;
			in>>s;
			G.insert(s);
		}

		multiset<si, greater<si>> B;
		for(si b = 0; b != nB; ++b) {
			si s;
			in>>s;
			B.insert(s);
		}

		while(!G.empty() && !B.empty()){
			vec<si> reG,reB;

			si f=min(N,(si)min(G.size(),B.size()));
			for(si n = 0; n < f; ++n) {
				si g=*G.begin();
				si b=*B.begin();
				G.erase(G.begin());
				B.erase(B.begin());
				fight(g,b);
				if(g!=0)reG.push_back(g);
				if(b!=0)reB.push_back(b);
			}
			
			G.insert(reG.begin(),reG.end());
			B.insert(reB.begin(),reB.end());
		}

		if(G.size()==0){
			if(B.size()==0){
				out<<"green and blue died\n";
			}else{
				out<<"blue wins\n";
				for(auto&& b : B) {
					out<<b<<"\n";
				}
			}
		}else{
			out<<"green wins\n";
			for(auto&& g : G) {
				out<<g<<"\n";
			}
		}
	}
}
