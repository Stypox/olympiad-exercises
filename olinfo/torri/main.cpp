#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct SegmentTree {
	static int higherPowerOf2(int x) {
		int res = 1;
		while (res < x) res *= 2;
		return res;
	}

	vector<int> data;
	SegmentTree(int n) : data(2 * higherPowerOf2(n), numeric_limits<int>::max()) {}

	int query(int i, int a, int b, int x, int y) {
		if (b <= x || a >= y) return numeric_limits<int>::max();
		if (b <= y && a >= x) return data[i];

		return min(query(i*2,   a, (a+b)/2, x, y),
		           query(i*2+1, (a+b)/2, b, x, y));
	}

	int update(int i, int a, int b, int x, int v) {
		if (x < a || x >= b) return data[i];
		if (a == b-1) {
			assert(a == x);
			return data[i] = v;
		}

		return data[i] = min(update(i*2,   a, (a+b)/2, x, v),
		                     update(i*2+1, (a+b)/2, b, x, v));
	}

	int query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

	void update(int x, int v) {
		update(1, 0, data.size()/2, x, v);
	}
};

struct Tower {
	int h,c;
};

signed main() {
	constexpr int maxH = 1001;
	int N;
	in >> N;

	vector<Tower> towers(N);
	int totCost = 0;
	for(int n=0; n<N; ++n) {
		in >> towers[n].h >> towers[n].c;
		totCost += towers[n].c;
	}

	SegmentTree costForHeightSt(maxH);
	for(int h=0; h<maxH; ++h) {
		costForHeightSt.update(h, totCost);
	}

	for(int n=0; n<N; ++n) {
		int minCostOfHigherTower = costForHeightSt.query(towers[n].h+1, maxH);
		int costIfStoppedHere = minCostOfHigherTower - towers[n].c;

		int currCostForThisHeight = costForHeightSt.query(towers[n].h, towers[n].h+1);
		if (costIfStoppedHere < currCostForThisHeight) {
			costForHeightSt.update(towers[n].h, costIfStoppedHere);
		}
	}

	out << costForHeightSt.query(0, maxH) << endl;
}
