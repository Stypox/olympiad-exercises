#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

map<long long int, int> m;

void aggiungi(long long int id) {
	m[id]++;
}

void togli(long long int id) {
	m[id]--;
}

int conta(long long int id) {
	return m[id];
}
