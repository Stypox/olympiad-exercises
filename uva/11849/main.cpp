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

int main() {
	while(1) {
		si N,M;
		in>>N>>M;
		if(N==0&&M==0)break;

		set<si> numsA;
		for(int n = 0; n != N; ++n) {
			si num;
			in>>num;
			numsA.insert(num);
		}

		si res=0;
		for(int m = 0; m != M; ++m) {
			si num;
			in>>num;
			res += (numsA.find(num) != numsA.end());
		}

		out<<res<<"\n";
	}
}
