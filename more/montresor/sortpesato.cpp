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

	vector<int> V(N);
	for(int n=0;n<N;++n){
		in>>V[n];
		V[n]--;
	}

	int S=0;
	vector<bool> seen(N, false);
	for(int n=0;n<N;++n){
		if(!seen[n]) {
			seen[n] = true;
			int cur=V[n];
			while (cur != n) {
				seen[cur] = true;
				++S;
				cur=V[cur];
			}
		}
	}

	out<<S<<" "<<0<<"\n";
}
