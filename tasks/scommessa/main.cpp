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
	vec<si> C(N);
	for(auto&& c : C)
		in>>c;

	if(N==1) {
		out<<"1\n"<<C[0];
	}
	else {
		vec<si> R;

		si evenSoFar = 0;
		if (C[0]%2 == 0) {
			R.push_back(C[0]);
			++evenSoFar;
		}

		for(int n = 1; n != N; ++n) {
			if(C[n]%2 == 0) {
				if (n%2 == 0 && evenSoFar == n/2)
					R.push_back(C[n]);
				++evenSoFar;
			}
		}

		out<<R.size()<<"\n";
		for(auto&& r : R)
			out<<r<<" ";
	}
}