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
	T(*merge)(const T&, const T&);
	vector<T> data;

	T query(int i, int a, int b, int x, int y) {
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
	SegmentTree(int n, const T& neutralValue, T(*merge)(const T&, const T&)) :
		neutralValue{neutralValue}, merge{merge}, data(2 * higherPowerOf2(n), neutralValue) {}

	T query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

	void update(int x, const T& v) {
		update(1, 0, data.size()/2, x, v);
	}
};

struct Data {
	int all, left, right, inside;
};

signed main() {
	int N, Q;
	in>>N>>Q;

	SegmentTree<Data> st1(
		N,
		Data{0,0,0,0},
		[](const Data& l, const Data& r) {
			return Data{
				l.all + r.all,
				max(l.all + r.left, l.left),
				max(r.all + l.right, r.right),
				max({l.inside, r.inside, l.right + r.left})
			};
		}
	);

	// st2 is just the opposite of st1 (panama sums can be from one or the other)
	SegmentTree<Data> st2 = st1;

	auto updateValue = [&](int n, int v) {
		if (n%2 == 1) {
			st1.update(n, Data{-v, 0, 0, 0});
			st2.update(n, Data{v, v, v, v});
		} else {
			st1.update(n, Data{v, v, v, v});
			st2.update(n, Data{-v, 0, 0, 0});
		}
	};

	for(int n=0; n<N; ++n){
		int v;
		in>>v;
		updateValue(n, v);
	}

	for(int q=0; q<Q; ++q){
		int t, al, br;
		in>>t>>al>>br;
		if (t == 1) {
			updateValue(al-1, br);
		} else {
			out << max(st1.query(al-1, br).inside, st2.query(al-1, br).inside) << "\n";
		}
	}
}
