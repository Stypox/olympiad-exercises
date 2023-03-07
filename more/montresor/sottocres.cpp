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
#define cout Do not use cout!!!
#define cin Do not use cin!!!

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

signed main() {
    int N;
    in>>N;

    vector<int> V(N);
    for(int& v:V)in>>v;

    map<int,int> vtoi;
    vector<int> V2=V;
    sort(V2.begin(),V2.end());
    for(int n=0;n<N;++n){
        if(!vtoi.count(V2[n])) {
            int i=vtoi.size();
            vtoi[V2[n]]=i;
        }
    }

    SegmentTree<int> st(N,0,max);
    for(int n=0;n<N;++n){
        int i = vtoi[V[n]];
        int res = st.query(0, i+1) + V[n];
        if (res > st.query(i, i+1)) {
            st.update(i, res);
        }
    }

    out<<st.query(0,N)<<endl;
}
