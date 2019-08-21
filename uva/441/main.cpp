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
	si t=0;
	while(1){
		si K;
		in>>K;
		if(K==0)break;

		if(t!=0)out<<"\n";
		++t;

		vec<si> S(K);
		for(auto&& s : S) {
			in>>s;
		}

		for(si a=0;   a!=K-5; ++a)
		for(si b=a+1; b!=K-4; ++b)
		for(si c=b+1; c!=K-3; ++c)
		for(si d=c+1; d!=K-2; ++d)
		for(si e=d+1; e!=K-1; ++e)
		for(si f=e+1; f!=K;   ++f)
			out<<S[a]<<" "<<S[b]<<" "<<S[c]<<" "<<S[d]<<" "<<S[e]<<" "<<S[f]<<"\n";
	}
}
