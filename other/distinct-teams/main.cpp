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

uint64_t factorial(uint64_t n) {
	if (n == 0) return 1;
	return n * factorial(n-1);
}

void printa(int N, vector<pair<int, int>> allPairs) {
	for(int giorno=0; giorno<N-1; ++giorno) {
		if (!is_sorted(allPairs.begin() + giorno*(N/2-1), allPairs.begin() + giorno*(N/2-1) + N/2-1)) {
			return;
		}
	}

	for(int giorno=0; giorno<N-1; ++giorno) {
		out << 0 << "-" << giorno+1;
		for(int coppia=0; coppia<N/2-1; ++coppia) {
			auto [a, b] = allPairs[giorno*(N/2-1) + coppia];
			out << " " << a << "-" << b;
		}
		out << "\n";
	}
	out << "\n" << flush;
}

int32_t main() {
	int N;
	in >> N;

	vector<pair<int, int>> allPairs;
	for(int a=1; a<N; ++a) {
		for(int b=a+1; b<N; ++b) {
			allPairs.push_back({a, b});
		}
	}

	int fattibili = 0;
	uint64_t permutazioni = factorial(allPairs.size());
	cout << allPairs.size() << " " << permutazioni << "\n";
	for(uint64_t i=0; i<permutazioni; ++i) {
		if (i % 1000000 == 0) {
			cout << i << "     \r" << flush;
		}

		for(int giorno=0; giorno<N-1; ++giorno) {
			vector<bool> mask(N, false);
			mask[giorno+1] = true;
			for(int coppia=0; coppia<N/2-1; ++coppia) {
				auto [a, b] = allPairs[giorno*(N/2-1) + coppia];
				if (mask[a] || mask[b]) {
					goto nonFattibile;
				}
				mask[a] = true;
				mask[b] = true;
			}
		}
		++fattibili;
		printa(N, allPairs);

		nonFattibile:
		next_permutation(allPairs.begin(), allPairs.end());
	}

	out << "Totale fattibili = " << fattibili << "\n";
}
