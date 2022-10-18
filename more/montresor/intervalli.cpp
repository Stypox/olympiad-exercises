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

signed main() {
	int N;
	in>>N;

	// pairs of (position; opening (false) or closing (true))
	vector<pair<int,bool>> V(N*2);
	for(int n=0;n<N;++n){
		in>>V[n*2].first>>V[n*2+1].first;
		V[n*2+1].second=true;
	}

	sort(V.begin(), V.end());

	int lastPos = V[0].first, overlaps = 0;
	int bestStart = 0, bestEnd = 0;
	for (auto&& [pos, isClosing] : V) {
		if (overlaps == 0 && (bestEnd - bestStart) < (pos - lastPos)) {
			bestStart = lastPos;
			bestEnd = pos;
		}
		overlaps += (isClosing ? -1 : 1);
		lastPos = pos;
		assert(overlaps >= 0);
	}

	if (bestEnd == 0) {
		out<<"0\n";
	} else {
		out<<bestStart<<" "<<bestEnd<<"\n";
	}
}
