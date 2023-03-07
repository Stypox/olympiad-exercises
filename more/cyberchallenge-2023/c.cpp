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
    int N, T;
    cin>>N>>T;

    vector<int> t(N);
    for(auto&ts:t){
        cin>>ts;
    }

    auto doable = [&](int M) {
        priority_queue<int, vector<int>, greater<int>> pq;
        int e=0;
        for(;e<M&&e<N;++e){
            pq.push(t[e]);
        }
        while(!pq.empty()){
            int prevt = pq.top();
            if (prevt > T) {
                return false;
            }
            pq.pop();

            if (e<N){
                pq.push(prevt+t[e]);
                e++;
            }
        }
        return true;
    };

    int a=1, b=N+1;
    while(b-a>1){
        int m=(b+a-1)/2;
        if (doable(m)) {
            b=m+1;
        } else {
            a=m+1;
        }
    }

    cout<<a<<"\n";
}
