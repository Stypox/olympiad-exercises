#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int32_t
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
	int N,X;
	in>>N>>X;
	vector<int> last(X+1, 0), next(X+1);

	for(int n=0;n<N;++n){
		int value, price;
		in>>value>>price;

		for(int x=0;x<=X;++x){
			if (x - price >= 0) {
				next[x] = max(last[x], last[x - price] + value);
			} else {
				next[x] = last[x];
			}
		}
		swap(last, next);
	}

	out<<*max_element(last.begin(), last.end());
}
