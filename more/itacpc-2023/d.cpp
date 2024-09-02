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

struct Sdata {
    string s;
    bool reversed;
    int i;

    bool operator<(const Sdata& other) const {
        return tie(s,reversed,i) < tie(other.s,other.reversed,other.i);
    }
};

signed main() {
    int N;
    cin>>N;

    vector<Sdata> strings;
    for(int n=0;n<N;++n){
        string s;
        cin>>s;
        strings.push_back({s,false,n});
        strings.push_back({string{s.rbegin(), s.rend()},true,n});
    }

    sort(strings.begin(), strings.end());
    //deb(strings);

    int ways = 0;
    for(int n=0;n<2*N;++n){
        for(int a=n+1;a<2*N;++a){
            if (strings[a].reversed == strings[n].reversed || strings[a].i == strings[n].i) {
                continue;
            }
            string& sa = strings[a].s;
            string& sn = strings[n].s;
            if (sa.rfind(sn,0) != 0) {
                break;
            }

            assert(sa.length() - sn.length() >= 0);
            bool pal=true;
            for(int x=0;x<(sa.length() - sn.length())/2;++x){
                if(sa[sn.length()+x] != sa[sa.length()-x-1]) {
                    pal = false;
                    break;
                }
            }

            if (pal) {
                deb(n, sn, a, sa);
                ways++;
            }
        }
    }

    cout << ways << "\n";
}
