#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = int;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

int main() {
	si T;
   assert(1 == scanf("%d", &T));
	for(si t = 0; t != T; ++t) {
		si N, K;
		assert(2 == scanf("%d %d", &N, &K));

		vec<flt> aliveness(N, 1.L);
		vec<flt> prob0(N);
		priority_queue<pair<flt, si>> q;
		for (si n=0; n<N; ++n) {
			assert(1 == scanf("%Lf", &prob0[n]));
			q.push({prob0[n], n});
		}

		flt result = 0.L;
		for(si k = 0; k != K; ++k) {
			auto [prob, i] = q.top();
			q.pop();

			result+=prob;
			aliveness[i]-=prob;

			q.push({aliveness[i] * prob0[i], i});
		}

		result = floor(result * 1000000) / 1000000;
		printf("%.6Lf\n", result);
	}
}
