#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int N;
	cin >> N;

	int prevA = 0, prevB = numeric_limits<int>::max();
	bool doable=true;
	for (int n=0; n<N; ++n){
		int a, b;
		cin >> a >> b;

		if (a > prevB || b < prevA) {
			doable = false;
			break;
		}
		prevA = a;
		prevB = b;
	}

	cout << (doable ? "YES" : "NO") << endl;
}
