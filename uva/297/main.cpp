#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

constexpr int black = 0, white = 1, parent = -1;

struct Node {
	int type;
	vector<Node> children;

	Node(int type) : type{type} {}
};

Node readNode(char const*& s) {
	if (*s == 'p') {
		Node res = Node(parent);
		++s;
		for(int i=0;i<4;++i){
			res.children.push_back(readNode(s));
		}
		return res;
	} else if (*s == 'f') {
		++s;
		return Node(black);
	} else {
		++s;
		return Node(white);
	}
}

Node readNodeLine() {
	string s;
	getline(in, s);
	char const* cs = s.c_str();
	return readNode(cs);
}

int32_t main() {
	int T;
	in >> T;
	in.ignore();

	for(int t = 0; t != T; ++t) {
		Node a = readNodeLine();
		Node b = readNodeLine();

		function<int(const Node&, const Node&, int)> findBlackPixels
				= [&findBlackPixels](const Node& a, const Node& b, int level) -> int {
			if (a.type == parent) {
				if (b.type == parent) {
					return findBlackPixels(a.children[0], b.children[0], level-1)
						 + findBlackPixels(a.children[1], b.children[1], level-1)
						 + findBlackPixels(a.children[2], b.children[2], level-1)
						 + findBlackPixels(a.children[3], b.children[3], level-1);
				} else {
					return findBlackPixels(a.children[0], b, level-1)
						 + findBlackPixels(a.children[1], b, level-1)
						 + findBlackPixels(a.children[2], b, level-1)
						 + findBlackPixels(a.children[3], b, level-1);
				}
			} else if (b.type == parent) {
				// swap
				return findBlackPixels(b,a,level);
			} else {
				if (a.type == black || b.type == black) {
					return (1<<level)*(1<<level);
				} else {
					return 0;
				}
			}
		};

		out<<"There are "<<findBlackPixels(a,b,5)<<" black pixels.\n";
	}
}
