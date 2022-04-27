#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;

void inizia(int N, int M) {
	v.resize(M);
	v[0].resize(N);
	iota(v[0].begin(), v[0].end(), 0);
}

void sposta(int a, int b) {
	v[b].push_back(v[a].back());
	v[a].pop_back();
}

int controlla(int a, int i) {
	if (i >= v[a].size()) {
		return -1;
	}
	return v[a][i];
}
