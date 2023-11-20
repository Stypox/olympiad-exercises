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

bool solve(int a, int b) {
    if (a<33 || a>53 || b>52 || (a-33+9)/10>b/11) {
        return false;
    }

    int times=0;
    while(b>=11&&times<2) {
        int ascore = min(max((int)0, a-33), (int)10);
        a-=ascore;
        b-=11;
        out<<ascore<<" 11\n";
        ++times;
    }

    assert(a == 33);
    assert(b <= 30);
    for(int i=0;i<3;++i){
        int bscore = min(b, (int)10);
        a-=11;
        b-=bscore;
        out<<11<<" "<<bscore<<"\n";
    }

    return true;
}

signed main() {
	int T;
    in>>T;
    while(T--){
        int A,B;
        in>>A>>B;

        if (!solve(A, B)) {
            out<<"-1 -1\n";
        }

        #ifdef DEBUG
        out<<endl;
        #endif
    }
}
