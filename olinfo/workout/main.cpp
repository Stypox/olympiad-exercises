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
void print(vec<si> v) {
	for(auto&& vi : v)
		cout<<vi<<" ";
	cout<<"\n";
}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
void print(vec<si> v) {};
#endif

int main() {
	si N;
	in>>N;
	vec<si> pos, neg;
	for(int n = 0; n != N; ++n) {
		si F;
		in>>F;
		if(F<0) neg.push_back(F);
		else pos.push_back(F);
	}

	sort(pos.begin(), pos.end());
	sort(neg.rbegin(), neg.rend());
	vec<si> sumsToEnd(pos.size());
	partial_sum(pos.rbegin(), pos.rend(), sumsToEnd.rbegin());

	print(neg);
	print(pos);
	print(sumsToEnd);

	si sumBefore = 0;
	ui oldPosi = 0, posi = 0, negi = 0;
	while (1) {
		si bestSoFar = numeric_limits<si>::max();
		while(posi != pos.size()) {
			deb("VAL", sumsToEnd[posi], sumBefore + sumsToEnd[oldPosi] - sumsToEnd[posi] - neg[negi]);
			si val = max(sumsToEnd[posi], sumBefore + sumsToEnd[oldPosi] - sumsToEnd[posi] - neg[negi]);
			if (val>bestSoFar) {
				break;
			}
			else {
				++posi;
				bestSoFar = val;
			}
		}

		deb(sumBefore, oldPosi, posi, negi, bestSoFar);

		for(ui p = oldPosi; p != posi; ++p) {
			sumBefore += pos[p];
			out<<pos[p]<<" ";
		}
		sumBefore += neg[negi];
		out<<neg[negi]<<" ";

		++negi;
		oldPosi = posi;
		if (negi == neg.size() || posi == pos.size()) break;
	}

	for(ui n = negi; n != neg.size(); ++n)
		out<<neg[n]<<" ";
	for(ui p = posi; p != pos.size(); ++p)
		out<<pos[p]<<" ";
}
