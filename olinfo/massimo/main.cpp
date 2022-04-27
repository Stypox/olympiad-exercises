#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

int trova_massimo(int N, vector<int> V) {
	return *max_element(V.begin(), V.end());
}
