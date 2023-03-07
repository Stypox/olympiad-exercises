#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

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
    int C,N;
    in>>C>>N;

    vector<int> P(N), V(N);
    for (int n=0;n<N;++n){
        in>>P[n]>>V[n];
    }

    vector<int> mem(C+1,0);
    for(int n=N-1;n>=0;--n){
        for(int c=C;c>=P[n];--c){
            mem[c]=max(mem[c],mem[c-P[n]]+V[n]);
        }
    }

    out<<*max_element(mem.begin(), mem.end())<<endl;
}
