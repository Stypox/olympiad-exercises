#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int N,M;
	cin>>N>>M;

	vector<int> P(N), X(M+1), cumP(N+1,0);
	for(int n=0;n<N;++n){
		cin>>P[n];
		cumP[n+1]=cumP[n]+P[n];
	}
	for(int m=0;m<M;++m){
		cin>>X[m+1];
	}
	sort(X.begin(), X.end());
	X[0]=-X[1]-200;
	X.push_back(2*N*100 - X.back() + 200);

	auto cumPAt = [&cumP](int i) {
		if (i >= (int)cumP.size()) return cumP.back();
		if (i < 0) return cumP.front();
		return cumP[i];
	};
	deb(X);
	deb(cumP);

	int res=0;
	for(int m=0;m<M+1;++m){
		int l=X[m]/100 + 1;
		int r=l;
		while(l<=r && r*100<X[m+1]){
			int lmar=200*l-X[m];
			int rmar=200*r-X[m+1];
			if (lmar > rmar) {
				deb(l,r,"ok", cumPAt(r+1), cumPAt(l));
				res=max(res, cumPAt(r+1)-cumPAt(l));
				++r;
			} else {
				deb(l,r,"no");
				++l;
			}
		}
	}

	cout<<res<<"\n";
}