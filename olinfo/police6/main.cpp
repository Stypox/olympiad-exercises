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

signed main() {
	int N, M, L;
	in >> N >> M >> L;

	vector<int> starts(N);
	for (int n = 0; n < N; ++n) {
		in >> starts[n];
		starts[n] -= M;
	}
	starts.push_back(L);

	queue<int> ends;
	ends.push(0);
	int curr = 1;
	int res = numeric_limits<int>::max();
	for (int n = 0; n < N+1; ++n) {
		while (!ends.empty() && ends.front() < starts[n]) {
			ends.pop();
			--curr;
			res = min(res, curr);
		}

		if (!ends.empty() && ends.front() == starts[n]) {
			ends.pop();
			--curr;
		}

		ends.push(starts[n] + 2*M);
		++curr;
		if (starts[n] >= 0) {
			res = min(res, curr);
		}
	}

	out << res << endl;
}
