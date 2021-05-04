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
	int N,T;
	in>>N>>T;

	vector<int> H;
	multiset<int> used;
	for(int n=0;n<N;++n){
		int h;
		in>>h;
		H.push_back(h);
		used.insert(h % T);
	}

	sort(H.begin(), H.end());

	int lasth=-1;
	for (int h:used){
		if(h > lasth+1){
			out<<lasth+1;
			return 0;
		}
		lasth=h;
	}
	if (T > lasth+1) {
		out<<lasth+1;
		return 0;
	}

	for(int n=0;n<N;++n){
		auto it = used.find(H[n] % T);
		used.erase(it, next(it));
		if (used.count(H[n] % T) == 0) {
			out<<H[n]+T;
			return 0;
		}
	}
}
