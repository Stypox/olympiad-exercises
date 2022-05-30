template<class T>
class SegmentTree {
	static int higherPowerOf2(int x) {
		int res = 1;
		while (res < x) res *= 2;
		return res;
	}

	const T neutralValue;
	const T&(*merge)(const T&, const T&);
	vector<T> data;

	const T& query(int i, int a, int b, int x, int y) {
		if (b <= x || a >= y) return neutralValue;
		if (b <= y && a >= x) return data[i];

		return merge(
			query(i*2,   a, (a+b)/2, x, y),
			query(i*2+1, (a+b)/2, b, x, y)
		);
	}

	const T& update(int i, int a, int b, int x, const T& v) {
		if (x < a || x >= b) return data[i];
		if (a == b-1) {
			assert(a == x);
			return data[i] = v;
		}

		return data[i] = merge(
			update(i*2,   a, (a+b)/2, x, v),
			update(i*2+1, (a+b)/2, b, x, v)
		);
	}

public:
	SegmentTree(int n, const T& neutralValue, const T&(*merge)(const T&, const T&)) :
		neutralValue{neutralValue}, merge{merge}, data(2 * higherPowerOf2(n), neutralValue) {}

	const T& query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

	void update(int x, const T& v) {
		update(1, 0, data.size()/2, x, v);
	}
};