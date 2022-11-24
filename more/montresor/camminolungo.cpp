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

struct Node{
    vector<int> to;
    int longest=-1;
};

signed main() {
    int N,M;
    in>>N>>M;

    vector<Node> nodes(N);
    for(int m=0;m<M;++m){
        int a,b;
        in>>a>>b;
        nodes[a].to.push_back(b);
    }

    function<int(int)> rec = [&](int i) -> int {
        if(nodes[i].longest != -1) return nodes[i].longest;
        nodes[i].longest=0;
        for(int e:nodes[i].to){
            nodes[i].longest=max(nodes[i].longest, 1+rec(e));
        }
        return nodes[i].longest;
    };

    int res=0;
    for(int n=0;n<N;++n){
        res=max(res,rec(n));
    }

    out<<res<<"\n";
}
