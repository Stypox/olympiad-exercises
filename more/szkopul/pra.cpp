#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Range {
	int index;
	int from, to;
};

bool setCmp(const Range* a, const Range* b) {
	return a->to < b->to;
}

signed main() {
	int N;
	unsigned int K;
	cin>>N>>K;

	vector<Range> ranges(N);
	for (int n=0;n<N;++n){
		ranges[n].index = n+1;
		cin>>ranges[n].from>>ranges[n].to;
	}

	sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) { return a.from < b.from; });

	int bestRangesLength = 0;
	multiset<Range*, decltype(&setCmp)> rangeSet(&setCmp);

	for (int n=0;n<N;++n){
		Range testRng;
		testRng.to = ranges[n].from;
		//cerr<<n<<" a "; for (auto e : rangeSet) cerr<<e->index<<" "; cerr<<"\n";
		rangeSet.erase(rangeSet.begin(), rangeSet.upper_bound(&testRng));

		rangeSet.insert(&ranges[n]);
		if (rangeSet.size() > K) {
			auto end = rangeSet.begin();
			end++;
			rangeSet.erase(rangeSet.begin(), end);
		}
		assert(rangeSet.size() <= K);

		if (rangeSet.size() == K) {
			int length = (*rangeSet.begin())->to - ranges[n].from;
			if (length > bestRangesLength) {
				bestRangesLength = length;
			}
		}
	}

	rangeSet.clear();
	for (int n=0;n<N;++n){
		Range testRng;
		testRng.to = ranges[n].from;
		rangeSet.erase(rangeSet.begin(), rangeSet.upper_bound(&testRng));

		rangeSet.insert(&ranges[n]);
		if (rangeSet.size() > K) {
			auto end = rangeSet.begin();
			end++;
			rangeSet.erase(rangeSet.begin(), end);
		}
		assert(rangeSet.size() <= K);

		if (rangeSet.size() == K) {
			int length = (*rangeSet.begin())->to - ranges[n].from;
			if (length == bestRangesLength) {
				break;
			}
		}
	}

	assert(rangeSet.size() == K);
	assert(bestRangesLength > 0);
	cout << bestRangesLength << "\n";
	for (auto r : rangeSet) {
		cout << r->index << " ";
	}
}
