#pragma region
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#pragma endregion

bool associabili(const int N, int* const marks2, int* const marks5) {
	std::sort(marks2, marks2 + N);
	std::sort(marks5, marks5 + N);
	for (int n = 0; n < N; ++n) {
		if (marks2[n] >= marks5[n])
			return false;
	}
	return true;
}
