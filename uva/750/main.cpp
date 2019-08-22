#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;
using Chess = array<array<bool, 8>, 8>;

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

void db(Chess chess) {
	for(auto&& column : chess) {
		debc(column);
	}
}
Chess remch(Chess chess, si a, si b) {
	for(int am = a-1; am >= 0; --am) {
		chess[am][b] = true;
		if (b+am-a >= 0) chess[am][b+am-a] = true;
		if (b-am+a < 8)  chess[am][b-am+a] = true;
	}
	for(int am = a+1; am < 8; ++am) {
		chess[am][b] = true;
		if (b-am+a >= 0) chess[am][b-am+a] = true;
		if (b+am-a < 8)  chess[am][b+am-a] = true;
	}
	for(int bm = 0; bm != 8; ++bm) {
		chess[a][bm] = true;
	}
	return chess;
}
array<si, 8> setPos(array<si, 8> positions, si coln, si rown) {
	positions[coln] = rown;
	return positions;
}

si soln;

void run(Chess chess, array<si, 8> positions, si coln) {
	if (coln >= 8) {
		++soln;
		out<<setw(2)<<soln<<"     ";
		
		for(auto&& pos : positions)
			out<<" "<<pos+1;
		out<<"\n";
		return;
	}

	if (positions[coln] >= 0) {
		run(chess, positions, coln+1);
	} else {
		for(int rown = 0; rown != 8; ++rown) {
			if (!chess[coln][rown]) {
				run(remch(chess, coln, rown), setPos(positions, coln, rown), coln+1);
			}
		}
	}
}

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si A,B;
		in>>B>>A;
		A--; B--;
		soln = 0;

		Chess chess;
		array<si, 8> positions;

		for(auto&& col : chess)
			fill(col.begin(), col.end(), false);
		fill(positions.begin(), positions.end(), -1);

		chess = remch(chess, A, B);
		positions[A]=B;

		if (t!=0) out<<"\n";
		out<<"SOLN       COLUMN\n";
		out<<" #      1 2 3 4 5 6 7 8\n\n";
		run(chess, positions, 0);
	}
}
