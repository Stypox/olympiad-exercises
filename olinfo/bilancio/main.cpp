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

struct SegmentTree {
	vector<int> dat, idx;
	SegmentTree(int N) {
		int s=1;
		while(s<N) s*=2;
		s*=2;
		dat.resize(s);
		idx.resize(s);
		iota(idx.begin() + s/2, idx.end(), 0);
	}

	void update(int x, int v, int a, int b, int i) {
		if (x<a || x>=b) return;
		if (b-a == 1) {
			dat[i] = v;
			return;
		}

		update(x, v, a, (a+b)/2, i*2);
		update(x, v, (a+b)/2, b, i*2+1);

		if (dat[i*2] <= dat[i*2+1]) {
			dat[i]=dat[i*2];
			idx[i]=idx[i*2];
		} else {
			dat[i]=dat[i*2+1];
			idx[i]=idx[i*2+1];
		}
	}

	pair<int, int> query(int x, int y, int a, int b, int i) {
		deb(x,y,a,b,i);
		if (a>=y || b<=x) return {numeric_limits<int>::max(), x};
		if (a>=x && b<=y) return {dat[i], idx[i]};
		return min(query(x, y, a, (a+b)/2, i*2),
					  query(x, y, (a+b)/2, b, i*2+1));
	}
};

signed main() {
	int N,K;
	in>>N>>K;

	vector<int> U(N);
	SegmentTree st(N);
	deb(st.dat, st.idx);
	for (int n = 0; n < N; ++n) {
		in >> U[n];
		st.update(n, U[n], 0, st.dat.size()/2, 1);
	}
	deb(st.dat, st.idx);

	int u = 0;
	while (1) {
		if (K == N)
			break;
		else if (K == 0) {
			for(int n = 0; n != N; ++n)
				out<<U[u+n]<<" ";
			break;
		}
		int minIdx = st.query(u, u + K + 1, 0, st.dat.size()/2, 1).second;
		deb(u, u+K+1, " ",  minIdx, distance(U.begin(), min_element(U.begin()+u, U.begin()+u+K+1)));
		out<<U[minIdx]<<" ";

		int diff = minIdx - u;
		K -= diff;
		N -= diff + 1;
		u += diff + 1;
	}
}
