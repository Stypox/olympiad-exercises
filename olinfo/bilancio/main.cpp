#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

si higherPow2(si v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

struct ST {
	vec<si> vals;
	vec<si> data;

	void build(si i, si L, si R) {
		if (L==(R-1)) {
			data[i]=L;
		} else {
			build(i*2,   L,       (L+R)/2);
			build(i*2+1, (L+R)/2, R      );

			if (vals[data[i*2]] < vals[data[i*2+1]]) {
				data[i] = data[i*2];
			} else {
				data[i] = data[i*2+1];
			}
		}
	}

	ST(const vec<si>& init) {
		vals = vector<si>(init);
		vals.resize(higherPow2(init.size()), numeric_limits<si>::max());

		data = vector<si>(2*vals.size());
		build(1, 0, vals.size());
	}

	si query(si i, si L, si R, si a, si b) {
		if (L>=b || R<=a) return -1;
		if (L>=a && R<=b) return data[i];

		si m1 = query(i*2,   L,       (L+R)/2, a, b);
		si m2 = query(i*2+1, (L+R)/2, R,       a, b);

		if (m1 == -1) return m2;
		if (m2 == -1) return m1;

		if (vals[m1] < vals[m2]) {
			return m1;
		} else {
			return m2;
		}
	}

	si query(si a, si b) {
		return query(1, 0, vals.size(), a, b);
	}
};

void erase(si N, si K, const vec<si>& U) {
	ST st(U);

	si u = 0;
	while (1) {
		if (K == N)
			break;
		else if (K == 0) {
			for(si n = 0; n != N; ++n)
				out<<U[u+n]<<" ";
			break;
		}
		si minIdx = st.query(u, u+K+1);
		out<<U[minIdx]<<" ";

		si diff = minIdx - u;
		K -= diff;
		N -= diff + 1;
		u += diff + 1;
	}
}

int main() {
	si N,K;
	in>>N>>K;

	vec<si> U(N);
	for (si n = 0; n < N; ++n) {
		in >> U[n];
	}
	
	erase(N, K, U);
}
