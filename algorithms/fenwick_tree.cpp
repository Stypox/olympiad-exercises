class FenwickTree {
	// least significant one bit
	static constexpr int lsOne(int x) { return x & (-x); }
	vector<int> data;

	int query(int b) {
		int sum=0;
		for(; b!=0; b-=lsOne(b))
			sum += data[b];
		return sum;
	}

public:
	FenwickTree(int N) : data(N+1, 0) {}
	int query(int a, int b) { return query(b) - query(a-1); }
	void adjust(int i, int delta) { for(; i<data.size(); i+=lsOne(i)) data[i] += delta; }
	void set(int i, int value) { adjust(i, value - query(i,i)); }
};
