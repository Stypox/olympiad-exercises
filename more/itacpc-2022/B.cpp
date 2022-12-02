#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define in cin
#define out cout

struct Node {
    vector<int> to;
    bool used=false;
    int i;
};

signed main() {
    int N;
    in>>N;

    vector<Node> nodes(26);
    for(int n=0;n<N;++n){
        string s1,s2,s3;
        in>>s1>>s2>>s3;

        if (s2[0]=='>') swap(s1,s3);
        nodes[s1[0]-'a'].to.push_back(s3[0]-'a');
    }

    vector<int> res;
    function<void(int)> rec = [&](int i) {
        if(nodes[i].used) return;
        nodes[i].used=true;
        for(int e:nodes[i].to){
            rec(e);
        }
        res.push_back(i);
    };
    for(int i=0;i<26;++i){
        rec(i);
    }

    reverse(res.begin(), res.end());
    for(int i=0;i<26;++i){
        nodes[res[i]].i=i;
    }

    for(auto&& node:nodes){
        for(auto e:node.to) {
            if (nodes[e].i < node.i) {
                out<<":(\n";
                exit(0);
            }
        }
    }
    out<<":)\n";
}
