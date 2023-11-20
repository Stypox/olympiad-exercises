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
    int N, M;
    cin >> N >> M;

    vector<vector<int>> cons(N);
    for (int m=0; m<M; ++m) {
        int a,b;
        cin>>a>>b;
        --a; --b;
        cons[a].push_back(b);
        cons[b].push_back(a);
    }

    vector<int> dists(N, numeric_limits<int>::max());
    dists[0] = 0;
    queue<int> q;
    q.push(0);

    while(!q.empty()) {
        int a = q.front();
        deb(a, dists[a]);
        q.pop();

        for(auto b : cons[a]) {
            if (dists[b] == numeric_limits<int>::max()) {
                dists[b] = dists[a] + 1;
                q.push(b);
            }
        }
    }

    deb(dists);
    auto ma = *max_element(dists.begin(), dists.end());
    if (ma == numeric_limits<int>::max()) {
        cout << -1 << endl;
    } else {
        cout << ((int)ceil(log2(ma)) + 1) << endl;
    }
}
