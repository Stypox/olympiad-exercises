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

struct Kick {
	int x,y;

	bool operator<(const Kick& other) const {
		if (x == other.x) {
			return y<other.y;
		}
		return x<other.x;
	}
};

signed main() {
	int N,V;
	cin>>N>>V;

	vector<Kick> originalKicks(N);
	for(int n=0;n<N;++n){
		cin>>originalKicks[n].x;
	}
	for(int n=0;n<N;++n){
		cin>>originalKicks[n].y;
	}

	// filter out unreachable kicks
	vector<Kick> kicks;
	for(auto& [t, a] : originalKicks) {
		if (abs(a) <= V*t) {
			kicks.push_back({V*t - a, V*t + a});
		}
	}

	// sort by x to enforce a_n+1 - a_n <= v*(t_n+1 - t_n)
	sort(kicks.begin(), kicks.end());

	// find the lis on increasing y to enforce a_n - a_n+1 <= v*(t_n+1 - t_n)
	vector<int> lis(kicks.size(), numeric_limits<int>::max());
	for(auto& [x, y] : kicks) {
		*upper_bound(lis.begin(), lis.end(), y) = y;
	}

	// now both conditions are enforced, so we have |a_n+1 - a_n| <= v*(t_n+1 - t_n)
	cout<<find(lis.begin(), lis.end(), numeric_limits<int>::max())-lis.begin()<<"\n";
}