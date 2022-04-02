#include <bits/stdc++.h>
using namespace std;

constexpr const char* order = "qwertyuiopasdfghjklzxcvbnm";

int main() {
	char calcolato[27];
	for(int i = 0; i < 26; ++i) {
		calcolato[order[i]-'a'] = order[i+1];
	}

	int N;
	cin >> N;

	string s;
	cin >> s;

	for(int n = 0; n < N; ++n) {
		cout << calcolato[s[n]-'a'];
	}
	cout << endl;
}
