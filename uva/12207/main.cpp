#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

int32_t main() {
	int T=0;
	while(1){
		int P,C;
		in>>P>>C;
		if (P==0 && C==0) return 0;

		++T;
		out<<"Case "<<T<<":\n";
		
		deque<int> people(min(C, P));
		iota(people.begin(), people.end(), 1);

		for(int c=0;c<C;++c){
			char type;
			in>>type;
			in.ignore();
			if(type=='N') {
				int i=0;
				while(i==0) {
					i = people.front();
					people.pop_front();
				}
				people.push_back(i);
				out<<i<<"\n";
			} else {
				int i;
				in>>i;
				replace(people.begin(), people.end(), i, (int)0);
				people.push_front(i);
			}
		}
	}
}
