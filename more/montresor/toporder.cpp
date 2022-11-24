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
    int N,M;
    in>>N>>M;

    vector<vector<int>> nodes(N);
    vector<int> used(N,false);
    for(int m=0;m<M;++m){
        int a,b;
        in>>a>>b;
        nodes[a].push_back(b);
    }

    vector<int> res;
    function<void(int)> rec = [&](int i) {
        if(used[i]) return;
        used[i]=true;
        for(int e:nodes[i]){
            rec(e);
        }
        res.push_back(i);
    };

    for(int n=0;n<N;++n){
        rec(n);
    }

    for(auto it = res.rbegin(); it != res.rend(); ++it) {
        out<<*it<<" ";
    }
}
