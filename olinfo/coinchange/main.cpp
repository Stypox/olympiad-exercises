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

constexpr int vals[15] = {1, 2, 5, 10, 20, 50, 1'00, 2'00, 5'00, 10'00, 20'00, 50'00, 100'00, 200'00, 500'00};

signed main() {
    int tot=0;
    for(int i=0;i<15;++i){
        int v;
        in>>v;
        tot+=vals[i]*v;
    }

    int res[15];
    for(int i=14;i>=0;--i){
        res[i]=tot/vals[i];
        tot%=vals[i];
    }

    for(int i=0;i<15;++i){
        out<<res[i]<<" ";
    }
}
