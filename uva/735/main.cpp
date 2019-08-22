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

constexpr si possibleScores[] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,24,26,27,28,30,32,33,34,36,38,39,40,42,45,48,50,51,54,57,60};

int main() {
	while(1) {
		si N;
		in>>N;
		if(N<=0)break;

		si comb=0, perm=0;

		for(si a : possibleScores)
		for(si b : possibleScores)
		for(si c : possibleScores){
			if (a + b + c == N) {
				++perm;
				if(a <= b && b <= c) {
					++comb;
				}
			}
		}

		if (perm == 0) {
			out<<"THE SCORE OF "<<N<<" CANNOT BE MADE WITH THREE DARTS.\n";
		} else {
			out<<"NUMBER OF COMBINATIONS THAT SCORES "<<N<<" IS "<<comb<<".\n";
			out<<"NUMBER OF PERMUTATIONS THAT SCORES "<<N<<" IS "<<perm<<".\n";
		}
		out<<"**********************************************************************\n";
	}
	out<<"END OF OUTPUT\n";
}
