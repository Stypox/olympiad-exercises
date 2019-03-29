#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

int main() {
	si N;
	in>>N;

	vec<si> fib{1, 1};
	while(1) {
		si nextFib = fib.end()[-2] + fib.end()[-1];
		if(nextFib > N) break;
		else fib.push_back(nextFib);
		deb(nextFib);
	}

	si i = fib.size()-1;
	vec<bool> used(fib.size(), false);
	while(N!=0) {
		while(fib[i] > N) --i;
		N-=fib[i];
		used[i]=true;
	}

	for(auto&& u : used)
		out<<u;
}