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

struct Term {
    int par=-1;
    int rank=1;
    int zRelat=-1; // will be -1 for roots
};

signed main() {
	int N,M;
    in>>N>>M;

    vector<Term> terms(N);
    function<pair<int,int>(int)> root = [&](int a) -> pair<int,int> {
        if (terms[a].par == -1) return {a, 0};
        auto [par, zRelat] = root(terms[a].par);
        return {par, zRelat + terms[a].zRelat};
    };
    auto merge = [&](int a, int b, int z) -> bool {
        auto [ra, za] = root(a);
        auto [rb, zb] = root(b);

        if (ra == rb) {
            return za - zb == z;
        }

        if (terms[ra].rank > terms[rb].rank) {
            swap(ra,rb);
            swap(za,zb);
            swap(a,b);
            z=-z;
        }

        // now rb has surely the highest rank, connect ra to rb
        terms[ra].par=rb;
        terms[rb].rank=max(terms[rb].rank,terms[ra].rank+1);
        terms[ra].zRelat=z-za+zb;
        return true;
    };


    for(int m=0;m<M;++m){
        int a,b,z;
        in>>a>>b>>z;

        if (!merge(a,b,z)) {
            out<<m<<"\n";
            return 0;
        }
    }

    out<<M<<"\n";
    return 0;
}
