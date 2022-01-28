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
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"	";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int T;
	in >> T;

	for (int t = 0; t < T; ++t) {
		int N, tipi;
		in >> N >> tipi;

		vector<int> parentesi;
		for (int n = 0; n < N; ++n) {
			int K;
			in >> K;
			if (parentesi.size() != 0 && K == parentesi[parentesi.size() - 1]) {
				parentesi.pop_back();
			} else {
				parentesi.push_back(K);
			}
		}

		if (parentesi.size() == 0) {
			out << 1 << endl;
		} else {
			out << 0 << endl;
		}
	}
}
