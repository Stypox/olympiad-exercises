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
	while(1) {
		si N;
		in>>N;
		if(N==0) break;

		if(t!=0) out<<"\n";
		++t;

		out<<setfill('0');
		bool foundone=false;
		for(si abcde = 1234 - (1234%N) + N; abcde <= 98765; abcde += N) {
			si fghij = abcde / N;

			array<bool, 10> used{false, false, false, false, false, false, false, false, false, false};
			auto setused = [&](si num) {
				for(si a=0; a!=5; ++a, num/=10)
					used[num%10]=true;
			};

			setused(abcde);
			setused(fghij);
			if (count(used.begin(), used.end(), true) == 10) {
				foundone=true;
				out<<setw(5)<<abcde<<" / "<<setw(5)<<fghij<<" = "<<N<<"\n";
			}
		}
		if (!foundone) {
			out<<"There are no solutions for "<<N<<".\n";
		}
	}
}
