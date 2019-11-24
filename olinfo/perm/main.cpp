#pragma GCC optimize ("O3")

#define MOD 1000000007

int trova(int N) {
	if (N<=2) {
		return N;
	} 

	long long sum=2, fact=1;
	for(int n = 1; n <= N; ++n) {
		sum += fact;
		sum %= MOD;
		fact *= n;
		fact %= MOD;
	}
	return sum;
}
/*
#include <bits/stdc++.h>
std::ifstream in{"input.txt"};
std::ofstream out{"output.txt"};

int main() {
	int N;
	in>>N;
	out<<trova(N);
}*/
