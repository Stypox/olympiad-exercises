#pragma GCC optimize ("O3")
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
    int N;
    cin>>N;

    vector<pair<int,int>> v(N);
    for(int n = 0; n != N; ++n) {
        cin>>v[n].second>>v[n].first;
    }

    sort(v.begin(), v.end());
    int curr=0, last=-1, best=0;
    for(int n = 0; n != N; ++n) {
        if (v[n].first != last) {
            best = max(best, curr);
            last = v[n].first;
        }
        curr += v[n].second;
    }

    cout << best << "\n";
}
