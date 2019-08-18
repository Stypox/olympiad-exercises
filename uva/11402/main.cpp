#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = int_fast32_t;
using ui = uint_fast32_t;
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

struct SegmentTree {
	vec<ui> l;
	ui n;
	
	void build(const ui i, const ui L, const ui R, const vec<ui>& init) {
		if (L==R) {
			l.at(i)=init.at(L);
		} else {
			build(2*i,     L,           (L+R)/2, init);
			build(2*i + 1, (L+R)/2 + 1, R,       init);
			l.at(i) = l.at(i*2) + l.at(i*2 + 1);
		}
	}

	ui query(const ui i, const ui L, const ui R, const ui a, const ui b) {
		if (L>b || R<a) return 0;
		if (L>=a && R<=b) return l.at(i);

		si s1 = query(i*2, L, (L+R)/2, a, b);
		si s2 = query(i*2 + 1, (L+R)/2 + 1, R, a, b);
		return s1+s2;
	}

	template<ui action>
	void set(const ui i, const ui L, const ui R, const ui a, const ui b) {
		if (L>b || R<a) {
			return;
		} else if (L==R) {
			if (action==0)      l.at(i)=0;
			else if (action==1) l.at(i)=1;
			else                l.at(i)=!l.at(i);
			return;
		}

		set<action>(i*2, L, (L+R)/2, a, b);
		set<action>(i*2 + 1, (L+R)/2 + 1, R, a, b);
		l.at(i) = l.at(i*2) + l.at(i*2 + 1);
	}

public:
	SegmentTree(const vec<ui>& init) : n{init.size()} {
		l.resize(3*n, 0);
		build(1, 0, n-1, init);
	}

	ui query(const ui a, const ui b) {
		return query(1, 0, n-1, a, b);
	}

	void set0(const ui a, const ui b) {
		return set<0>(1, 0, n-1, a, b);
	}
	void set1(const ui a, const ui b) {
		return set<1>(1, 0, n-1, a, b);
	}
	void invert(const ui a, const ui b) {
		return set<2>(1, 0, n-1, a, b);
	}

	void sdeb() {
		debc(l, "SegmentTree data: ");
	}
};

int main() {
	ui T;
	in >> T;

	for(ui t = 0; t != T; ++t) {
		out<<"Case "<<t+1<<":\n";
		ui M;
		in>>M;
		
		vec<ui> pirates;
		for(ui m = 0; m != M; ++m) {
			ui N;
			in>>N;
			in.ignore();

			vec<ui> curr;
			ch c=in.get();
			while(c!='\n') {
				curr.push_back(c=='1');
				c=in.get();
			}

			for(ui n = 0; n != N; ++n) {
				pirates.insert(pirates.end(), curr.begin(), curr.end());
			}
		}

		SegmentTree st{pirates};
		st.sdeb();

		ui Q, query=1;
		in>>Q;
		for(ui q = 0; q != Q; ++q) {
			ch action;
			ui a,b;
			in>>action>>a>>b;

			if(action=='F'){
				st.set1(a,b);
			} else if(action=='E'){
				st.set0(a,b);
			} else if(action=='I'){
				st.invert(a,b);
			} else{
				out<<"Q"<<query<<": "<<st.query(a,b)<<"\n";
				++query;
			}
		}
	}
}
