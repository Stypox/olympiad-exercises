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
    int N,K;
    cin>>N>>K;

    vector<pair<int,int>> v(N);
    for(int n=0;n<N;++n){
        cin>>v[n].first>>v[n].second;
    }

    sort(v.begin(), v.end());

    auto fattibile = [&](int maxn) -> bool {
        set<int> pq;
        int cosieliminati=0;
        for(int n=0;n<N;++n){
            deb(v[n], "before removing", pq);
            while (!pq.empty() && *pq.begin() < v[n].first) {
                pq.erase(pq.begin());
            }
            deb(v[n], "after removing", pq);

            pq.insert(v[n].second);
            deb(v[n], "after inserting", pq);
            if (pq.size() > maxn) {
                auto it = pq.end();
                --it;
                pq.erase(it);
                ++cosieliminati;
            }
            deb(v[n], "after removing maximum", pq);

            if (cosieliminati > K) {
                return false;
            }
        }

        return true;
    };

    int a=1, b=N+1;
    while (b > a+1) {
        int m = (a+b-1)/2;
        deb("m", a, b, m);
        if (fattibile(m)) {
            b = m+1;
        } else {
            a = m+1;
        }
    }

    cout<<a<<"\n";
}
