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

#define MOD 1'000'000'007

struct Node {
    int par = 0, rank = 1;
};

signed main() {
	int R,C,N;
    in>>R>>C>>N;

    vector<Node> parents(1);
    function<int(int)> root = [&](int a) -> int {
        if (parents[a].par == 0) return a;
        return parents[a].par = root(parents[a].par);
    };
    auto merge = [&](int a, int b) -> int {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }

        auto ra = root(a);
        auto rb = root(b);
        if (ra == rb) {
            return ra;
        }

        if (parents[ra].rank > parents[rb].rank) {
            swap(ra,rb);
            swap(a,b);
        }

        // now rb has surely the highest rank, connect ra to rb
        parents[ra].par=rb;
        parents[rb].rank=max(parents[rb].rank,parents[ra].rank+1);
        return rb;
    };

    unordered_map<int, int> rrm,ccm,trm,tlm;
    for(int n=0;n<N;++n){
        int rr,cc;
        in>>rr>>cc;
        --rr; --cc;

        int newpar = 0;
        for (auto& par : vector<int>{rrm[rr], ccm[cc], trm[rr-cc], tlm[rr+cc]}) {
            newpar = merge(par, newpar);
        }
        if (newpar == 0) {
            newpar = parents.size();
            parents.emplace_back();
        }

        rrm[rr] = newpar;
        ccm[cc] = newpar;
        trm[rr-cc] = newpar;
        tlm[rr+cc] = newpar;
    }

    assert(parents[0].par == 0);

    int res=1;
    bool skip=true;
    for(auto& par : parents){
        if (skip) {
            skip=false;
            continue;
        }
        if (par.par == 0) {
            res *= 2;
            res %= MOD;
        }
    }

    out<<res<<endl;
}
