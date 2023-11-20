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

bool solve(int a, int b, int wona, int rem) {
    if (a < (3-wona)*11 || rem <= 0) {
        return false;
    }

    if (wona == 2 && a == 11 && b < 11) {
        out<<a<<" "<<b<<endl;
        return true;
    }

    if (wona < 2) {
        int lim = min(b, (int64_t)10);
        for (int i=0;i<=lim;++i){
            if (solve(a-11, b-i, wona+1, rem-1)) {
                out<<11<<" "<<i<<endl;
                return true;
            }
        }
    }

    if (rem > (3-wona) && b >= 11) {
        for (int i=0;i<11;++i){
            if (solve(a-i, b-11, wona, rem-1)) {
                out<<i<<" "<<11<<endl;
                return true;
            }
        }
    }

    return false;
}

signed main() {
	int T;
    in>>T;
    while(T--){
        int A,B;
        in>>A>>B;

        if (!solve(A, B, 0, 5)) {
            out<<"-1 -1\n";
        }

        #ifdef DEBUG
        out<<endl;
        #endif
    }
}
