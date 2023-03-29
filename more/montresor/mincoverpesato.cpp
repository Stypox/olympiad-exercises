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
    vector<int> children;
    int weight;
};

signed main() {
    int N;
    in>>N;
    
    vector<Node> nodes(N);
    for(int n=0;n<N;++n){
        in>>nodes[n].weight;
    }
    for(int n=0;n<N-1;++n){
        int p,f;
        in>>p>>f;
        nodes[p].children.push_back(f);
    }

    function<pair<int,int>(int)> rec = [&](int n) {
        int ifTaken = nodes[n].weight;
        int ifNotTaken = 0;
        for(auto c:nodes[n].children) {
            auto p = rec(c);
            ifTaken += min(p.first,p.second);
            ifNotTaken += p.first;
        }
        return pair<int,int>(ifTaken, ifNotTaken);
    };

    auto p = rec(0);
    out << min(p.first,p.second);
}
