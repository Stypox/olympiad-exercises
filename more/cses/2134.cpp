#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

constexpr int LIFTING_SIZE = 20;

void remove(vector<int>& vec, int val) {
	vec.erase(remove(vec.begin(), vec.end(), val), vec.end());
}

constexpr int higherPowerOf2(int n) {
	int x=1;
	while (x < n) x*=2;
	return x;
}

template<typename T>
struct SegmentTree {
	int size;
	T neutral;
	T (*combine)(const T&, const T&);
	vector<T> mem;

	T query(int a, int b, int x, int y, int i) {
		if (a >= y || b <= x) return neutral;
		if (x >= a && y <= b) return mem[i];

		return combine(
			query(a, b, x, (x+y)/2, i*2),
			query(a, b, (x+y)/2, y, i*2+1)
		);
	}

	T update(int a, T v, int x, int y, int i) {
		if (a < x || a >= y) return mem[i];
		if (a == x && a == y-1) return mem[i] = v;

		return mem[i] = combine(
			update(a, v, x, (x+y)/2, i*2),
			update(a, v, (x+y)/2, y, i*2+1)
		);
	}

public:
	SegmentTree() = default;

	SegmentTree(
		int _size,
		T _neutral,
		T (*_combine)(const T&, const T&)
	) :
		size{higherPowerOf2(_size)},
		neutral{_neutral},
		combine{_combine},
		mem(2 * size, neutral) {}

	T query(int a, int b) {
		return query(a, b, 0, size, 1);
	}

	void update(int a, T v) {
		update(a, v, 0, size, 1);
	}
};

struct Node {
	int value;
	int depth;
	int subtreeSize;
	int heavyDepth;
	int heavyRoot;

	vector<int> children;
	array<int, LIFTING_SIZE> parents;

	SegmentTree<int> st;
};

signed main() {
	int N, Q;
	cin>>N>>Q;

	vector<Node> nodes(N);
	for(int n=0;n<N;++n){
		cin>>nodes[n].value;
	}

	for(int n=0;n<N-1;++n){
		int a,b;
		cin>>a>>b;
		a--; b--;
		nodes[a].children.push_back(b);
		nodes[b].children.push_back(a);
	}

	// build the tree
	function<int(int,int,int)> buildTree = [&](int i, int par, int depth) {
		auto& node = nodes[i];
		remove(node.children, par);
		node.parents[0] = par;
		node.depth = depth;

		node.subtreeSize = 1;
		for (int c : node.children) {
			node.subtreeSize += buildTree(c, i, depth+1);
		}

		return node.subtreeSize;
	};
	assert(buildTree(0, 0, 0) == N);

	// build heavy light decomposition segment trees
	function<void(int,vector<int>&)> buildHeavy = [&](int i, vector<int>& chain) {
		auto& node = nodes[i];
		node.heavyDepth = chain.size();
		bool createSegmentTree = chain.empty();

		chain.push_back(i);
		node.heavyRoot = chain[0];

		int maxChildSize=-1, maxChildIndex=-1;
		for (int c : node.children) {
			if (nodes[c].subtreeSize > maxChildSize) {
				maxChildSize = nodes[c].subtreeSize;
				maxChildIndex = c;
			}
		}

		for (int c : node.children) {
			if (c == maxChildIndex) {
				buildHeavy(c, chain);
			} else {
				vector<int> newChain;
				buildHeavy(c, newChain);
			}
		}

		if (createSegmentTree) {
			node.st = SegmentTree<int>(chain.size(), 0, [](const int& a, const int& b) { return max(a, b); });
			deb("building segment tree for chain", chain);
		}
	};
	vector<int> newChain;
	buildHeavy(0, newChain);

	// setup binary lifting for lowest common ancestor
	for(int i=1; i<LIFTING_SIZE; ++i) {
		for(int n=0; n<N; ++n) {
			nodes[n].parents[i] = nodes[nodes[n].parents[i-1]].parents[i-1];
		}
	}

	auto lift = [&](int x, int steps) {
		assert(steps >= 0);
		for(int i=0; i<LIFTING_SIZE; ++i) {
			if (steps & (1 << i)) {
				x = nodes[x].parents[i];
			}
		}
		return x;
	};

	auto lowestCommonAncestor = [&](int a, int b) {
		if (nodes[a].depth > nodes[b].depth) {
			swap(a, b);
		}
		b = lift(b, nodes[b].depth - nodes[a].depth);
		if (a == b) {
			return a;
		}

		for(int i=LIFTING_SIZE-1; i>=0; --i) {
			if (nodes[a].parents[i] != nodes[b].parents[i]) {
				a = nodes[a].parents[i];
				b = nodes[b].parents[i];
			}
		}

		assert(a != b);
		assert(nodes[a].parents[0] == nodes[b].parents[0]);
		return nodes[a].parents[0];
	};

	// update values in the tree
	auto updateValue = [&](int s, int x) {
		nodes[nodes[s].heavyRoot].st.update(nodes[s].heavyDepth, x);
	};

	// find max element along path
	function<int(int,int)> maxAlongPath = [&](int a, int ancestor) {
		if (nodes[a].heavyRoot == nodes[ancestor].heavyRoot) {
			deb("equal!", a, ancestor, nodes[a].heavyDepth + 1, nodes[ancestor].heavyDepth);
			return nodes[nodes[a].heavyRoot].st.query(nodes[ancestor].heavyDepth, nodes[a].heavyDepth + 1);
		} else {
			int branchMax = nodes[nodes[a].heavyRoot].st.query(0, nodes[a].heavyDepth + 1);
			int upMax = maxAlongPath(nodes[a].parents[0], ancestor);
			deb("different", a, ancestor, branchMax, upMax);
			return max(branchMax, upMax);
		}
	};

	// fill values in segment trees
	for (int n=0; n<N; ++n){
		updateValue(n, nodes[n].value);
	}
	for (int i=0; i<N; ++i){
		deb(i + 1, nodes[i].heavyDepth, nodes[i].heavyRoot, nodes[i].st.mem);
	}
	deb();

	// solve problem (use string for faster output)
	string s;
	while (Q--) {
		int tmp, sa, xb;
		cin>>tmp>>sa>>xb;
		if (tmp == 1) {
			--sa;
			updateValue(sa, xb);

		} else {
			assert(tmp == 2);
			--sa;
			--xb;

			int lca = lowestCommonAncestor(sa, xb);
			int maxa = maxAlongPath(sa, lca);
			int maxb = maxAlongPath(xb, lca);
			deb(sa+1, xb+1, lca+1, maxa, maxb);
			for (int i=0; i<N; ++i){
				deb(i + 1, nodes[i].st.mem);
			}
			deb();

			s += to_string(max(maxa, maxb));
			s += (Q == 0 ? "" : " ");
		}
	}
	cout << s << "\n";
}
