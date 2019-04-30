#pragma region
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#pragma endregion

int_fast8_t* countingSorted(const int* const marks, const int N) {
	auto result = new int_fast8_t[N];
	int counted[11] {0};

	for (int n = 0; n < N; ++n)
		++counted[marks[n]];
	
	for (int mark = 0, n = 0; mark <= 10; ++mark)
		for (const int countMax = n + counted[mark]; n < countMax; ++n)
			result[n] = mark;

	return result;
}

bool associabili(const int N, int* const marks2, int* const marks5) {
	int_fast8_t* sorted2 = countingSorted(marks2, N), * sorted5 = countingSorted(marks5, N);
	for (int n = 0; n < N; ++n) {
		if (sorted2[n] >= sorted5[n])
			return false;
	}
	return true;
}
