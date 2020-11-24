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
	while(1){
		int N;
		in>>N;
		if (N==0 || !in) break;

		int sum=0;
		multiset<int> bills;
		for(int n=0;n<N;++n){
			int K;
			in>>K;

			for (int k=0;k<K;++k){
				int b;
				in>>b;
				bills.insert(b);
			}

			auto end=bills.end();
			--end;
			sum+=(*end-*bills.begin());
			bills.erase(end);
			bills.erase(bills.begin());
		}

		out<<sum<<"\n";
	}
}
