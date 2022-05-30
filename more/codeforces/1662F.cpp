#include <bits/stdc++.h>
using namespace std;

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

int main() {
	int T;
	cin>>T;

	while(T--){
		int N, A, B;
		cin>>N>>A>>B;
		A--; B--;

		vector<int> P(N);
		for(auto& p:P) {
			cin>>p;
		}

		auto maxMerger = [](const pair<int, int>& a, const pair<int, int>& b) -> const pair<int, int>& {
			return a.second > b.second ? a : b; // keep the maximum
		};

		auto minMerger = [](const pair<int, int>& a, const pair<int, int>& b) -> const pair<int, int>& {
			return a.second < b.second ? a : b; // keep the minimum
		};

		SegmentTree<pair<int, int>> rightReach(N, {-1,-1}, maxMerger), leftReach(N, {-1,N}, minMerger);
		for(int n=0; n<N; ++n) {
			rightReach.update(n, {n, min(n+P[n], N-1)});
			leftReach.update(n, {n, max(n-P[n], 0)});
		}

		// queue handling
		queue<pair<int, int>> q;
		auto addToQueue = [&](int n, int d) {
			// remove all incoming edges
			rightReach.update(n, {n, -1});
			leftReach.update(n, {n, N});
			q.push({n,d});
		};
		addToQueue(A, 0);

		// main loop
		while(true) {
			auto [n, d] = q.front();
			q.pop();

			if (n == B) {
				cout<<d<<"\n";
				break;
			}

			// go right in all possible ways
			while(true) {
				auto [i, val] = leftReach.query(n+1, n+P[n]+1);
				if (val > n) {
					break;
				}
				addToQueue(i, d+1);
			}

			// go left in all possible ways
			while(true) {
				auto [i, val] = rightReach.query(n-P[n], n);
				if (val < n) {
					break;
				}
				addToQueue(i, d+1);
			}
		}
	}
}