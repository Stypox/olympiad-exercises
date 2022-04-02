#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define ull uint64_t

struct Node {
	int children[2] {-1, -1};
	bool terminal = false;
	ull waysChildren = 0;
};

struct Trie {
	vector<Node> nodes;
	int stateCount;

	Trie() {
		nodes.emplace_back();
		nodes.back().terminal = true;
	}

	Node& findOrCreate(const string& s) {
		int state = 0;
		for(int i=0; i<s.size()-1; i++) {
			char next = s[i] - '0';

			if (nodes[state].children[next] < 0) {
				nodes[state].children[next] = nodes.size();
				nodes.emplace_back();
			}

			state = nodes[state].children[next];
		}

		return nodes[state];
	}

	ull waysDfs(int state, int depth) {
		for (auto child : nodes[state].children) {
			if (child != -1) {
				nodes[state].waysChildren += waysDfs(child, depth-1);
			}
		}

		return nodes[state].terminal ? (1ull << depth) : nodes[state].waysChildren;
	}

	ull answer(const string& s, int totalBits) {
		Node& node = findOrCreate(s);
		int shift = totalBits - s.size() + 1;
		ull base = (shift == 64) ? 0 : (1ull << shift);
		return base - node.waysChildren;
	}
};

int main() {
	while (1) {
		int N, M;
		cin >> N >> M;
		if (N==0 && M==0) break;
		Trie trie;

		for(int n=0; n<N; n++) {
			string s;
			cin >> s;
			trie.findOrCreate(s).terminal = true;
		}

		trie.waysDfs(0, M);

		int K;
		cin >> K;
		for(int k=0; k<K; k++) {
			string s;
			cin >> s;
			cout << trie.answer(s, M) << endl;
		}
		cout << endl;
	}
}
