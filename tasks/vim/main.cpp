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

void valuta(int N, int C[], int L[], int P[]) {
	fill(P, P+N, 1);
	
	si sum = 0;
	for(int n = N-1; n >= 0; --n) {
		sum+=C[n]-L[n];
		if (sum<0) P[n]=0;
		else sum=0;
	}
	if (sum<0) {
		for(int n = N-1; n >= 0; --n) {
			sum+=C[n]-L[n];
			if (sum<0) P[n]=0;
			else break;
		}
	}
}

// remove the main() function on submission
int main() {
	int N;
	in>>N;
	int* C = new int[N], * L = new int[N], * P = new int[N];
	for(int n = 0; n != N; ++n)
		in>>C[n]>>L[n];
	
	valuta(N, C, L, P);

	for(int n = 0; n != N; ++n)
		out<<P[n]<<" ";
}