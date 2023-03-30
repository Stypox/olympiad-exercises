#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

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
    int V, F, M;
    in>>V>>F>>M;

    vector<vector<vector<double>>> mem(V+1, vector<vector<double>>(V+1, vector<double>(F+1, -1.0)));
    function<double(int,int,int)> H = [&](int v, int r, int f) -> double {
        if (v < 0 || r < 0 || f < 0) {
            return 0;
        }
        if (F-f+r+2*(V-v-r) >= M) {
            return (v+r)*f;
        }
        if (mem[v][r][f] != -1.0) {
            return mem[v][r][f];
        }

        return mem[v][r][f] = 1.0/(v+r+f)*(v*H(v-1,r+1,f) + r*H(v,r-1,f) + f*H(v,r,f-1));
    };

    out<<scientific<<setprecision(10)<<H(V,0,F)<<"\n";
}
