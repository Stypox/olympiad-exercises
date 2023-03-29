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
#define cout Do not use cout!!!
#define cin Do not use cin!!!

signed main() {
    string a, b;
    in>>a>>b;
    if (b.size() > a.size()) {
        swap(a,b);
    }

    int pesoPrev;
    vector<int> pesi(b.size(), 0);
    for(int i=0;i<a.size();++i){
        pesoPrev = 0;
        for(int j=0;j<b.size();++j){
            int nextPesoPrev = pesi[j];
            if (a[i] == b[j]) {
                pesi[j] = pesoPrev + 1;
            } else if (j > 0) {
                pesi[j] = max(pesi[j-1], pesi[j]);
            }
            pesoPrev = nextPesoPrev;
        }
        deb(pesi);
    }

    out<<pesi.back()<<endl;
}
