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

int biggerPowerOf2(int n) {
	int i=0;
	while(n!=0) {
		n>>=1;
		++i;
	}
	return 1<<i;
}

struct SegmentTree {
	struct Node {
		int maxh=0;
		bool shouldPropagate=false;
	};
	vector<Node> data;

	SegmentTree(int n) {
		n = biggerPowerOf2(n);
		data.resize(n*2);
	}

	// [a,b) -> building range
	// [x,y) -> current query range
	int addBuilding(int a, int b, int h, int x, int y, int i) {
		if (y <= a || x >= b) {
			// current query range outside of building
			return 0;
		}
		if (x >= a && y <= b) {
			if (data[i].maxh <= h) {
				data[i].maxh = h;
				data[i].shouldPropagate = true;
				return y-x;
			}

			if (data[i].shouldPropagate || i >= data.size() / 2) {
				// currently analyzing a section with all-equal values, so do not recurse further
				return 0;
			}
		}

		if (data[i].shouldPropagate) {
			// no need to propagate now if none of the propagated values will be updated by this query
			if (data[i].maxh > h) {
				return 0;
			}

			data[i*2].maxh = data[i].maxh;
			data[i*2+1].maxh = data[i].maxh;
			data[i*2].shouldPropagate = true;
			data[i*2+1].shouldPropagate = true;
			data[i].shouldPropagate = false;
		}

		int res = addBuilding(a, b, h, x, (x+y)/2, i*2)
			    + addBuilding(a, b, h, (x+y)/2, y, i*2+1);
		data[i].maxh = max(data[i*2].maxh, data[i*2+1].maxh);
		return res;
	}

	int addBuilding(int a, int b, int h) {
		return addBuilding(a, b, h, 0, data.size()/2, 1);
	}
};

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int N;
		in>>N;
		SegmentTree st(100100);

		int overlap = 0;
		for(int n=0;n<N;++n){
			int a, b, h;
			in>>a>>b>>h;
			overlap += st.addBuilding(a-1, b-1, h);
			/*deb(overlap);

			for(int i=0;i<st.data.size();++i) {
				deb(i, "->", st.data[i].maxh, st.data[i].shouldPropagate ? "shouldPropagate" : "done");
			}*/
		}


		out<<overlap<<"\n";
	}
}
