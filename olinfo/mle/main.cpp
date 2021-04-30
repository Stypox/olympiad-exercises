#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,class=decltype(*begin(declval<T>()))>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct SegmentTree {
	vector<int> dat;
	SegmentTree(int N) {
		int k=1;
		while (k<N) k*=2;
		dat.resize(k*2, -1);
	}

	void update(int x, int y, int c, int a, int b, int i) {
		//deb(x, y, c, a, b, i, dat);
		if (a>=y || b<=x || dat.at(i) != -1) return;
		if (a>=x && b<=y) {
			dat.at(i)=c;
			return;
		}
		update(x,y,c, a, (a+b)/2, i*2);
		update(x,y,c, (a+b)/2, b, i*2+1);
	}

	void prop(int a, int b, int i) {
		if (b-a == 1) return;
		if (dat.at(i*2)   == -1) dat.at(i*2)   = dat.at(i);
		if (dat.at(i*2+1) == -1) dat.at(i*2+1) = dat.at(i);
		prop(a, (a+b)/2, i*2);
		prop((a+b)/2, b, i*2+1);
	}
};

void Colora(int N, int Q, vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& murale) {
	deb(N, Q, A, B, C, murale);
	SegmentTree st(N);
	for(int q=Q-1;q>=0;--q){
		st.update(A.at(q), B.at(q)+1, C.at(q), 0, st.dat.size()/2, 1);
	}
	st.prop(0, st.dat.size()/2, 1);
	for(int n=0;n<N;++n){
		murale.at(n)=max(st.dat.at(st.dat.size()/2 + n), 0);
	}
}
