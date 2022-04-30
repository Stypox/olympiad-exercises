#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	srand(time(0));

	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N, K;
		cin>>N>>K;
		assert(K==8000);

		vector<int> estimations(N, -1);
		int lastTp=0;
		int followedCount=0;
		for (int k=0;k<K;++k){
			int R,P;
			cin>>R>>P;
			R--;

			if (estimations[R] != -1) {
				--followedCount;
				lastTp += 8;
			}
			estimations[R]=P;

			if (k == K-1) {
				continue;
			}

			++lastTp;
			if (lastTp >= K/100) {
				lastTp=0;

				int room;
				while (estimations[room = rand() % N] != -1);
				cout<<"T "<<room+1<<"\n"<<flush;

			} else {
				followedCount++;
				cout<<"W\n"<<flush;
			}
		}

		float sum=0;
		int cnt=0;
		for(int e:estimations) {
			if (e>=0) {
				sum+=e;
				cnt++;
			}
		}

		cout<<"E "<<(int)(sum/cnt*N/(2 + followedCount/5.0/(float)K))<<"\n"<<flush;
	}
}
