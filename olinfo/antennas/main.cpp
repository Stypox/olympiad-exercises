#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

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

struct Antenna {
	int l, r, s, t, reached=-1;
};

signed main() {
	int N, D;
	in>>N>>D;

	vector<Antenna> antennas(N);
	for(int n = 0; n != N; ++n) {
		int l, p;
		in>>l>>p>>antennas[n].s>>antennas[n].t;
		antennas[n].l = l + D*n;
		antennas[n].r = p + D*n;
	}

	auto minMerger = [](const pair<int, int>& a, const pair<int, int>& b) -> const pair<int, int>& {
		return a.second < b.second ? a : b; // keep the minimum
	};

	SegmentTree<pair<int,int>> st(N, {-1,numeric_limits<int>::max()}, minMerger);
	for(int n = 0; n != N; ++n) {
		st.update(n, {n, antennas[n].l});
	}

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq{};
	auto addToQueue = [&](int transmitTime, int i) {
		// remove all incoming edges
		st.update(i, {i, numeric_limits<int>::max()});
		pq.push({transmitTime,i});
	};
	addToQueue(antennas[0].s,0);

	while(!pq.empty()) {
		auto [transmitTime, i] = pq.top();
		antennas[i].reached = transmitTime;
		deb(i, transmitTime, antennas[i].l, antennas[i].r);
		pq.pop();

		while(true){
			auto [j, l] = st.query(i+1, N);
			if (l <= antennas[i].r) {
				int s = antennas[j].s, t = antennas[j].t;
				deb("   ", j, l, s, t);
				addToQueue(s + max((int)0, ((transmitTime - s + t) / t) * t), j);
			} else {
				break;
			}
		}
	}

	out<<antennas.back().reached<<endl;
}
