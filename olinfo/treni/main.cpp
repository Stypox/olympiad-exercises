#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

int tempo_massimo(int N, int A[], int B[]) {
	vector<int> mem(N,-1);
	function<int(int)> rec = [&](int n) {
		if (n==N-1) return A[n];
		if (n==N) return 0;
		if (mem[n] == -1) mem[n] = max(A[n] + rec(n+1), B[n+1] + rec(n+2));
		return mem[n];
	};

	return max(rec(0), B[0] + rec(1));
}
