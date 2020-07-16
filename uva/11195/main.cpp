#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

struct Chess {
	int N, r;
	vector<vector<bool>> bad;
	vector<int> queens; // queens[row] = column
	vector<bool> columnsUsed;
	vector<bool> diagonals1Used;
	vector<bool> diagonals2Used;

	Chess(int N) : N{N},
		r{0},
		bad(N, vector<bool>(N, false)),
		queens(N),
		columnsUsed(N, false),
		diagonals1Used(2*N - 1, false),
		diagonals2Used(2*N - 1, false) {}

	void setBad(int r, int c) {
		bad[r][c] = true;
	}

	bool canQueenBeAddedAt(int c) {
		return !(bad[r][c] || columnsUsed[c] || diagonals1Used[c+r] || diagonals2Used[N-1-c+r]);
	}

	void addQueen(int c) {
		queens[r]=c;
		columnsUsed[c]=true;
		diagonals1Used[c+r]=true;
		diagonals2Used[N-1-c+r]=true;
		++r;
	}

	void removeQueen(int c) {
		--r;
		// no need to change value of queens[r]
		columnsUsed[c]=false;
		diagonals1Used[c+r]=false;
		diagonals2Used[N-1-c+r]=false;
	}
};

int run(Chess& chess) {
	if (chess.r >= chess.N) {
		return 1;
	}
	
	int solutions = 0;
	for(int c = 0; c != chess.N; ++c) {
		if (chess.canQueenBeAddedAt(c)) {
			chess.addQueen(c);
			solutions += run(chess);
			chess.removeQueen(c);
		}
	}
	return solutions;
}

int32_t main() {
	int t=0;
	while(1) {
		int N;
		in>>N;
		if(N==0) break;
		
		Chess chess{N};
		for(int r = 0; r != N; ++r) {
			string tmp;
			in>>tmp;
			for(int c = 0; c != N; ++c)
				if (tmp[c] == '*')
					chess.setBad(r, c);
		}

		++t;
		out<<"Case "<<t<<": "<<run(chess)<<"\n";
	}
}
