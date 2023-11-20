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

#define P 31
#define MOD 1'000'000'009

int test(const string& s, int N) {
    int L = s.size();

    int curhash = 0;
    int Pn = 1;
    for (int i=0; i<N; i++){
        curhash *= P;
        curhash %= MOD;
        curhash += s[i];
        curhash %= MOD;

        Pn *= P;
        Pn %= MOD;
    }

    deb(curhash, (int)s[0]);
    unordered_map<int, int> m;
    m[curhash] = 0;
    for(int i=N; i<L; ++i){
        curhash *= P;
        curhash %= MOD;
        curhash += Pn * (MOD - s[i-N]);
        curhash += s[i];
        curhash %= MOD;

        if (m.contains(curhash)) {
            m[curhash] = -1;
        } else {
            m[curhash] = i-N+1;
        }
        deb(curhash);
    }

    int besti = L;
    for(auto& [h, i] : m) {
        if (i >= 0 && i < besti) {
            besti = i;
        }
    }

    deb(m);
    return (besti == L ? -1 : besti);
}

signed main() {
    string s;
    cin >> s;
    for (auto& c : s) {
        c -= 'A'-1;
    }

    // deb("res", test(s, 11));
    // return 0;

    int a=1, b=s.size();
    while (b > a+1) {
        int m = (a+b-1)/2;
        deb("m", a, b, m);
        if (test(s, m) >= 0) {
            b = m+1;
        } else {
            a = m+1;
        }
    }

    int offset = test(s, a);
    deb(a, b, offset);
    for (int i=offset; i<offset+a; ++i) {
        cout << (char)(s[i]+'A'-1);
    }
    cout << endl;
}
