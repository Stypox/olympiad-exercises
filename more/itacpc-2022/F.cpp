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

signed main() {
    int N,M,K;
    in>>N>>M>>K;

    vector<bitset<2000>> m1(2000);
    for(int m=0;m<M;++m){
        int a,b;
        in>>a>>b;
        a--; b--;
        m1[a][b]=true;
        m1[b][a]=true;
    }

    for(int i=0;i<2000;++i){
        for(int j=0;j<2000;++j){
            if (i != j && (m1[i] & m1[j]).count() >= K) {
                out<<"YES\n";
                exit(0);
            }
        }
    }
    out<<"NO\n";
}
