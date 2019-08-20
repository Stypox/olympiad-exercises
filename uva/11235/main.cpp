#include <bits/stdc++.h>
using namespace std;

using si = long long;
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

struct ST {
	si N;
	vec<si> data;

	void build(si i, si L, si R, const vec<si>& init) {
		if (L==R) {
			data[i]=init[L];
		} else {
			build(i*2,   L,           (L+R)/2, init);
			build(i*2+1, (L+R)/2 + 1, R,       init);
			data[i] = max(data[i*2], data[i*2+1]);
		}
	}

	ST(const vec<si>& init) : N(init.size()), data(4*N+4) {
		build(1, 0, N, init);
	}

	si query(si i, si L, si R, si a, si b) {
		if (L>b || R<a) return -1;
		if (L>=a && R<=b) return data[i];

		si m1 = query(i*2,   L,           (L+R)/2, a, b);
		si m2 = query(i*2+1, (L+R)/2 + 1, R,       a, b);
		return max(m1, m2);
	}

	si query(si a, si b) {
		if (b<a) return -1;
		if (a==b) return 1;
		return query(1, 0, N, a-1, b-1);
	}
};

int main() {
	while(1) {
		si N,Q;
		in>>N>>Q;
		if(N==0 || (!in)) break;

		si lastv=222222, start=0;
		vec<si> freq(N+1), borr(N+1), borl(N+1);
		for(int n = 1; n <= N; ++n) {
			si val;
			in>>val;
			if(val!=lastv) {
				fill(freq.begin()+start, freq.begin()+n, n-start);
				fill(borr.begin()+start, borr.begin()+n, n-1);
				fill(borl.begin()+start, borl.begin()+n, start);

				lastv=val;
				start=n;
			}
		}
		fill(freq.begin()+start, freq.end(), N-start+1);
		fill(borr.begin()+start, borr.end(), N);
		fill(borl.begin()+start, borl.end(), start);
		debc(freq, "Freq: ");
		debc(borr, "Borr: ");
		debc(borl, "Borl: ");

		ST st{vec<si>{freq.begin()+1, freq.end()}};
		for(int q = 0; q != Q; ++q) {
			si a,b;
			in>>a>>b;

			si res;
			si aAligned = borr[a]+1, bAligned = borl[b]-1;
			if (aAligned-1>bAligned) {
				res = b-a+1;
			} else {
				res = max({aAligned-a, b-bAligned, st.query(aAligned, bAligned)});
			}
			
			out<<res<<"\n";
		}
	}
}
