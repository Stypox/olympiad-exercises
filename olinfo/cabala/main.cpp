#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll occulta(int N, int M) {
	ll maxRemainder=0;
	function<void(int, ll, int)> rec = [&](int n, ll numSoFar, int prev) {
		if (n>N) return;
		maxRemainder = max(maxRemainder, numSoFar%M);

		if (prev != 3) rec(n+1, numSoFar*10 + 3, 3);
		if (prev != 6) rec(n+1, numSoFar*10 + 6, 6);
		if (prev != 9) rec(n+1, numSoFar*10 + 9, 9);
	};
	rec(0,0,0);
	return maxRemainder;
}

int main() {
    FILE *fr, *fw;
    int T, N, M, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &T));
    for (i=0; i<T; i++) {
        assert(2 == fscanf(fr, "%d %d", &N, &M));
        fprintf(fw, "%d ", occulta(N, M));
    }

    fprintf(fw, "\n");
    fclose(fr);
    fclose(fw);
    return 0;
}