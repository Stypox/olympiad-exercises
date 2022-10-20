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

	vector<int> V(N+1);
	int P = 0;
	for(int n=1;n<=N;++n){
		in>>V[n];
		P += V[n];
	}

	int S = 0;
	vector<bool> seen(N+1, false);
	for(int n=1;n<=N;++n){
		if(!seen[n]) {
			seen[n] = true;
			int cur = V[n];
			int mincycle = n;
			int lencycle = 1;

			while (cur != n) {
				if (cur < mincycle) {
					mincycle = cur;
				}
				++lencycle;

				seen[cur] = true;
				cur=V[cur];
			}

			S += lencycle - 1;
			P += min(
				// drag the smallest item along the cycle
				mincycle * (lencycle - 2),
				// or import the 1 into the cycle and drag 1 along the cycle
				mincycle + lencycle + 1
			);
		}
	}

	out<<S<<" "<<P<<"\n";
}
