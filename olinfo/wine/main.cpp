#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int N, K;
vector<int> V;

int numWithSmallerCost(int cost) {
	int result = 0, end = 0, sum = 0;
	for (int start = 0; start < N; ++start) {
		while(end < N && sum + V[end] <= cost) {
			sum += V[end];
			++end;
		}
		result += end-start;
		sum -= V[start];
	}
	return result;
}

signed main() {
	cin >> N >> K;

	V.resize(N);
	for (int n = 0; n < N; ++n) {
		cin >> V[n];
	}

	// binary search the biggest cost such that numWithSmallerCost(m) < K
	int a=0, b=300000000000000LL;
	while (b > a+1) {
		int m = (b+a)/2;

		if (numWithSmallerCost(m) < K) {
			a = m;
		} else {
			b = m;
		}
	}

	int remainingWithEqualCost = K - numWithSmallerCost(a);
	assert(remainingWithEqualCost > 0);
	int end = 0, sum = 0;
	for (int start = 0; start < N; ++start) {
		while(end < N && sum + V[end] <= a + 1) {
			sum += V[end];
			++end;
		}
		if (sum == a + 1) {
			--remainingWithEqualCost;
			if (remainingWithEqualCost == 0) {
				cout << start << " " << end - 1 << endl;
				break;
			}
		}
		sum -= V[start];
	}
	assert(remainingWithEqualCost == 0);
}
