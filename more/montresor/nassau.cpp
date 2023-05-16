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

    vector<vector<float>> mem(2, vector<float>(F+V-1, 0.0));

    for (int hp2=0; hp2<V; ++hp2){
        for (int hp1=0; hp1<F+V-1; ++hp1) {
            for (bool puoColpireVascello : array<bool,2>{false, true}) {
                float& res = mem[puoColpireVascello][hp1];

                int colpiRimasti = M - (2*V + F) + (2*hp2 + hp1 + 2 + puoColpireVascello);
                deb(hp1, hp2, puoColpireVascello, colpiRimasti);
                if (colpiRimasti == 0) {
                    res = 1.0;
                    continue;
                }
                if (colpiRimasti < 0 || (F-1-(hp1-(V-1-hp2)))<0) {
                    res = 0.0;
                    continue;
                }

                res = 1.0 / (hp1 + hp2 + 2.0) * (
                    (puoColpireVascello ? mem[false][hp1]   : 0.0) * 1.0 +
                    (hp2 > 0            ? mem[puoColpireVascello][hp1+1] : 0.0) * hp2 +
                    (hp1 > 0            ? mem[puoColpireVascello][hp1-1] : 0.0) * hp1
                );
            }
        }
    }

    out << scientific << setprecision(10);
    out << mem[true][F-1] * V * F << "\n";
    deb(mem);
}
