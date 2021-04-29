#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node{
	int par;
	vector<int> chi;
	int label;
	int bestLabel;
};

struct LabelMap{
	int bestLabel;
	int bestCount=-1;
	unordered_map<int, int> m;

	void add(int label, int count) {
		int& newCount = m[label];
		newCount += count;
		if (newCount > bestCount || (newCount == bestCount && label < bestLabel)) {
			bestCount = newCount;
			bestLabel = label;
		}
	}

	void addAll(const LabelMap& other) {
		for(auto [k,v] : other.m) {
			add(k, v);
		}
	}

	int size() {
		return m.size();
	}
};

vector<int> solve(int N, vector<int> p, vector<int> a) {
	vector<Node> nodes(N);
	for(int n=1;n<N;++n){
		nodes[n].par=p[n];
		nodes[p[n]].chi.push_back(n);
	}
	for(int n=0;n<N;++n){
		nodes[n].label=a[n];
	}

	vector<int> bestLabels(N);
	function<LabelMap(int)> dfs = [&](int i) {
		LabelMap res; // map from label to occourences
		res.add(nodes[i].label, 1);

		for(auto e:nodes[i].chi) {
			LabelMap newLabels = dfs(e);
			if (newLabels.size() > res.size()) swap(newLabels, res);
			res.addAll(newLabels);
		}

		bestLabels[i] = res.bestLabel;
		return res;
	};

	dfs(0);
	return bestLabels;
}
