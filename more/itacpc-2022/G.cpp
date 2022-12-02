#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define in cin
#define out cout

struct pii {
    int m, s, i;

    bool operator<(const pii& other) const {
        return (m-s) > (other.m-other.s);
    }
};

signed main() {
    // does not work
    int N;
    in>>N;

    vector<int> v(N);
    for(int n=0;n<N;++n) {
        in>>v[n];
    }

    vector<int> sums(N);
    sums[N-1]=v[N-1];
    for(int n=N-2;n>=0;--n){
        sums[n]=sums[n+1]+v[n];
    }
    sums.push_back(0);

    vector<int> terza(N);
    terza[0]=v[0];

    int mins=v[0];
    multiset<int> mCurInQueue;
    priority_queue<pii> pq;
    pq.push(pii{v[0], 0, 0});
    mCurInQueue.insert(v[0]);
    for(int n=1;n<N-1;++n){
        mins += v[n];
        deb("mins", mins, mCurInQueue);
        while(!pq.empty()) {
            int news=pq.top().s+sums[pq.top().i+1]-sums[n+1], m=pq.top().m;
            deb("here", m, news, sums[pq.top().i+1], sums[n+1]);
            if (news >= m) {
                deb("removing");
                mCurInQueue.erase(mCurInQueue.lower_bound(m));
                mins = min(mins, news);
                pq.pop();
            } else {
                break;
            }
        }

        int res;
        if (mCurInQueue.size()) {
            deb(n, mins, *mCurInQueue.begin());
            res = min(mins, *mCurInQueue.begin());
        } else {
            deb(n, mins);
            res = mins;
        }
        res = max(res, v[n]);
        deb("res", res);

        pq.push({res, 0, n});
        mCurInQueue.insert(res);
        terza[n]=res;
    }

    deb(terza);
}
