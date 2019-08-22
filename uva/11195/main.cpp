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

struct Chess {
	si N;
	vec<vec<bool>> used;

	Chess(si N_) : N{N_}, used(N, vec<bool>(N, false)) {}

	void setBad(si r, si c) {
		used[r][c] = true;
	}

	void setQueen(si r, si c) {
		for(si rm = r-1; rm >= 0; --rm) {
			used[rm][c] = true;
			if (c+rm-r >= 0) used[rm][c+rm-r] = true;
			if (c-rm+r < N)  used[rm][c-rm+r] = true;
		}
		for(int rm = r+1; rm < N; ++rm) {
			used[rm][c] = true;
			if (c-rm+r >= 0) used[rm][c-rm+r] = true;
			if (c+rm-r < N)  used[rm][c+rm-r] = true;
		}
		for(int cm = 0; cm != N; ++cm) {
			used[r][cm] = true;
		}
	}

	void db() {
		for(auto&& column : used) {
			debc(column);
		}
	}
};

si soln;

void run(Chess chess, si coln) {
	if (coln >= chess.N) {
		++soln;
		return;
	}
	
	for(int rown = 0; rown != chess.N; ++rown) {
		if (!chess.used[rown][coln]) {
			Chess newChess = chess;
			newChess.setQueen(rown, coln);
			run(newChess, coln+1);
		}
	}
}

int main() {
	si t=0;
	while(1) {
		soln = 0;
		si N;
		in>>N;
		if(N==0) break;
		
		Chess chess{N};
		for(int r = 0; r != N; ++r) {
			str tmp;
			in>>tmp;
			for(int c = 0; c != N; ++c)
				if (tmp[c] == '*')
					chess.setBad(r, c);
		}

		run(chess, 0);
		++t;
		out<<"Case "<<t<<": "<<soln<<"\n";
	}
}
