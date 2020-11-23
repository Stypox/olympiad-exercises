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

#define M 1000000007

int higherPowerOf2(int n){
	for(int i=1;;++i){
		if((1<<i) >= n) return (1<<i);
	}
}

int gcdImpl(int a, int b) {
	if (b==0) return a;
	return gcdImpl(b, a%b);
}

int gcd(int a, int b) {
	if (a<b) swap(a,b);
	return gcdImpl(a,b);
}

class SegmentTree {
public:
	vector<int> m;

	/*
	[a,b) -> intervallo richiesto
	[x,y) -> intervallo corrente
	*/
	int query(int a, int b, int x, int y, int i) {
		if (y <= a || x >= b) return 0;
		if (x >= a && y <= b) return m[i];

		return gcd(query(a,b, x,       (x+y)/2, i*2),
		           query(a,b, (x+y)/2, y,       i*2+1));
	}

	/*
	a -> punto richiesto
	[x,y) -> intervallo corrente
	*/
	void set(int a, int v, int x, int y, int i) {
		if (a >= y || a < x) return;
		if (x+1 == y) {
			assert(a==x);
			m[i]=v;
			return;
		}

		set(a,v, x,       (x+y)/2, i*2);
		set(a,v, (x+y)/2, y,       i*2+1);

		m[i] = gcd(m[2*i], m[2*i+1]);
	}

public:
	SegmentTree(int N) : m(higherPowerOf2(N)*2, 0) {}

	int query(int a, int b) {
		return max((int)1, query(a, b, 0, m.size()/2, 1));
	}

	void set(int a, int v) {
		set(a, v, 0, m.size()/2, 1);
	}
};

int32_t main() {
	int N,K;
	in>>N>>K;

	SegmentTree st(N);
	for(int n=0;n<N;++n){
		int v;
		in>>v;
		st.set(n, v);
	}
	debc(st.m);

	vector<vector<pair<int,int>>> mem(N, vector<pair<int,int>>(K+1, {-1,-1}));
	function<pair<int,int>(int, int)> rec = [&](int n, int k) -> pair<int,int> {
		deb(n,k);

		if (k==0 && n<=N) {
			deb(n,k,"exit", n==N, k==0);
			return {0,1};
		} else if (n+k>N) {
			deb(n,k,"ERROR", n==N, k==0);
			return {0,0};
		}

		if (mem[n][k].first == -1) {
			int s=0,m=0; // s = sum, m = multiplier
			if (n+k<N) {
				auto sm = rec(n+1,k); // sm = sum, multiplier
				s += sm.first;
				m += sm.second;
				s %= M;
				m %= M;
			}

			for (int i=n+1; i<N-k+2; ++i){
				auto sm = rec(i,k-1); // sm = sum, multiplier
				s += sm.second * st.query(n,i) + sm.first;
				m += sm.second;
				s %= M;
				m %= M;
			}

			mem[n][k].first = s;
			mem[n][k].second = m;
		}
		deb(n,k," -> ",mem[n][k].first, mem[n][k].second);
		return mem[n][k];
	};

	out<<rec(0,K).first<<"\n";

	for (int k=1;k<=K;++k){
		for(int n=0;n<N;++n){
			//cout<<"("<<mem[n][k].first<<","<<mem[n][k].first<<") ";
		}
		//cout<<"\n";
	}
}
