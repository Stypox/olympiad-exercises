#include <bits/stdc++.h>
using namespace std;

int higherPowerOf2(int i) {
	int r=1;
	while (r < i) r*=2;
	return r;
}

struct SegmentTree {
    static int higherPowerOf2(int x) {
        int res = 1;
        while (res < x) res *= 2;
        return res;
    }

	vector<int> data;
	SegmentTree(int n) : data(2 * higherPowerOf2(n), 0) {}

	int query(int i, int a, int b, int x, int y) {
		if (b <= x || a >= y) return 0;
		if (b <= y && a >= x) return data[i];

		return query(i*2,   a, (a+b)/2, x, y)
		     + query(i*2+1, (a+b)/2, b, x, y);
	}

	int update(int i, int a, int b, int x, int v) {
		if (x < a || x >= b) return data[i];
		if (a == b-1) {
			assert(a == x);
			return data[i] = v;
		}

		return data[i] = update(i*2,   a, (a+b)/2, x, v)
			            + update(i*2+1, (a+b)/2, b, x, v);
	}

	int query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

	void update(int x, int v) {
		update(1, 0, data.size()/2, x, v);
	}
};

int main() {
	int T;
	cin>>T;

	while(T--){
		int N, A, B;
		cin>>N>>A>>B;

		vector<int> P(N);
		for(auto& p:P) {
			cin>>p;
		}


	}
}