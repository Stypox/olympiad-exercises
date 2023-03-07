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
    int Q, N;
    cin>>Q>>N;
    cin.ignore();

    string c;
    cin>>c;
    cin.ignore();

    for(int n=0;n<N;++n){
        string s;
        cin>>s;
        cin.ignore();

        int correct=0;
        for(int q=0;q<Q;++q){
            correct+=(c[q]==s[q]);
        }
        cout<<correct<<"\n";
    }
}
