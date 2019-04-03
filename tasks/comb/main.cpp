#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = int;
using ui = unsigned int;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

constexpr ui maxN = 1000000;
int8_t primeMem[4*maxN];

bool isPrime(si n) {
	if (primeMem[n] != -1) return primeMem[n];
	if (n<=1 || n%2==0) return false;

	const si squareRoot = sqrt(n);
	for(si div = 2; div <= squareRoot; ++div) {
		if ((n/div)*div == n) {
			primeMem[n] = 0;
			return false;
		}
	}
	primeMem[n] = 1;
	return true;
}

void suddividi(int N, int* X, int* Y) {
	fill(primeMem, primeMem+4*N+5, -1);
	vector<si> even(N), odd(N);

	si n = N*2+2;
	generate(even.begin(), even.end(), [&n](){ return n-=2; });
	n = -1;
	generate(odd.begin(), odd.end(), [&n](){ return n+=2; });
	
	si outIndex = 0;
	while(1) {
		if (even.size() == 0) break;
		si temp = odd[0];
		copy(odd.begin()+1, odd.end(), odd.begin());
		odd.back() = temp;
		
		if (isPrime(even[0]+odd[0])) {
			si firstNonPrime = 0;
			if (odd[0] == 1)
				firstNonPrime = odd.size();
			else
				while (odd[firstNonPrime] != 1) ++firstNonPrime;
			
			for(si n = 0; n != firstNonPrime; ++n) {
				X[outIndex] = even[n];
				Y[outIndex] = odd[n];
				++outIndex;
			}
			even.erase(even.begin(), even.begin() + firstNonPrime);
			odd.erase(odd.begin(), odd.begin() + firstNonPrime);
		}
	}
}

// remove the main() function on submission
int main() {
	si N;
	in>>N;

	int X[maxN], Y[maxN];	
	suddividi(N, X, Y);

	for(si n = 0; n != N; ++n)
		out<<X[n]<<" "<<Y[n]<<"\n";
}