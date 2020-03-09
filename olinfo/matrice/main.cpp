#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

vector<int> getPrimes() {
	vector<int> result{};
	result.push_back(2);

	for(int i = 3; i != 100100; ++i) {
		bool found = true;
		for (int v : result) {
			if (i%v==0) {
				found=false;
				break;
			}
		}

		if (found) {
			//cout<<i<<" ";
			result.push_back(i);
		}
	}

	return result;
}

int32_t main() {
	vector<int> primes = getPrimes();

	int N, M;
	in>>N>>M;

	vector<vector<int>> board(N, vector<int>(M));
	for(int n = 0; n != N; ++n) {
		for(int m = 0; m != M; ++m) {
			int val;
			in>>val;

			if (val==0) {
				board[n][m] = 2;
			} else if (val==1) {
				board[n][m] = 1;
			} else {
				auto up = lower_bound(primes.begin(), primes.end(), val);
				board[n][m] = *up - val;
			}

			//cout<<board[n][m]<<" ";
		}
		//cout<<"\n";
	}

	int minsum = numeric_limits<int>::max();

	for(int n = 0; n != N; ++n) {
		int sum=0;
		for(int m = 0; m != M; ++m)
			sum+=board[n][m];
		minsum=min(sum,minsum);
	}

	for(int m = 0; m != M; ++m) {
		int sum=0;
		for(int n = 0; n != N; ++n)
			sum+=board[n][m];
		minsum=min(sum,minsum);
	}

	out<<minsum;
}
