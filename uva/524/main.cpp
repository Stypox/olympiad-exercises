#include <bits/stdc++.h>
using namespace std;

using si = int_fast16_t;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

constexpr array<si, 11> primes{2,3,5,7,11,13,17,19,23,29,31};
si N;

bool isPrime(si n) {
	return find(primes.begin(), primes.end(), n) != primes.end();
}

void rec(vec<si> seq, vec<bool> used) {
	// debc(seq, "Seq : ");
	// debc(used, "Used: ");

	if (seq.size() == N) {
		if (isPrime(seq.back()+seq.front())) {
			out<<1;
			for(int i = 1; i != seq.size(); ++i)
				out<<" "<<seq[i];
			out<<"\n";
		}
	} else {
		for(int n = 1; n != (N+1); ++n) {
			if(!used[n-1] && isPrime(seq.back() + n)) {
				vec<si> newseq = seq;
				newseq.push_back(n);

				vec<bool> newused = used;
				newused[n-1]=true;

				rec(newseq, newused);
			}
		}
	}
}

int main() {
	si t=0;
	while(1) {
		in>>N;
		if(!in) break;

		vec<si> seq{1};
		vec<bool> used(N, false);
		used[0]=true;

		if(t!=0) out<<"\n";
		++t;
		out<<"Case "<<t<<":\n";
		rec(seq, used);
	}
}
