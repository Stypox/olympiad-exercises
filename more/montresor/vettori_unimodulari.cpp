#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

int main() {
    vector<int> v{19,17,16,13,12,10,9,8,6,4,3,2,1,4,7,8,11,12,16,17,20};

    int a=0,b=v.size()-1;
    while(b-a>=3) {
        int m1=a+(b-a)/3;
        int m2=a+(b-a)*2/3;

        int va=v[a], v1=v[m1], v2=v[m2], vb=v[b];
        if(v1 > v2) {
            a = m1;
        } else {
            b = m2;
        }
    }

    int res = v[a];
    for(int i=a+1;i<=b;++i){
        res = min(res, v[i]);
    }

    deb(res);
}