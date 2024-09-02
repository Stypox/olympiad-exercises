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
    int N,M,Cpiu,Cmeno;
    cin>>N>>M>>Cpiu>>Cmeno;

    vector<vector<int>> cons(N);
    for(int n=0;n<M;++n) {
        int a,b;
        cin>>a>>b;
        --a; --b;
        cons[a].push_back(b);
        cons[b].push_back(a);
    }

    vector<bool> seen(N);
    int numedges=0,numnodes=0;
    function<void(int)> dfs = [&](int i) {
        if (seen[i]) return;
        seen[i] = true;
        numnodes += 1;
        numedges += cons[i].size();

        for(int con : cons[i]) {
            dfs(con);
        }
    };

    int numcomps = 0;
    int tot = 0;
    for(int n=0;n<N;++n){
        if (!seen[n]) {
            numedges = 0;
            numnodes = 0;
            dfs(n);
            numedges /= 2;
            deb(numedges, numnodes);
            tot += (numedges - (numnodes-1))*Cmeno;
            ++numcomps;
        }
    }

    tot += (numcomps-1)*Cpiu;
    cout << tot << "\n";
}
