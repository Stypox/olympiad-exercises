#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

struct Node{
    vector<int> to;
    int tin=-1, tactive=-1;
    bool inside=false;
};

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
ostream&operator<<(ostream&o,const Node&p){cout<<"("<<p.to<<", "<<p.tin<<", "<<p.tactive<<")";return o;}
#else
#define deb(...)
#endif
#define cout Do not use cout!!!
#define cin Do not use cin!!!

signed main() {
    int N,M;
    in>>N>>M;

    vector<Node> nodes(N);
    for(int m=0;m<M;++m){
        int a,b;
        in>>a>>b;
        nodes[a].to.push_back(b);
    }

    int t=0,res=0;
    stack<int> s;
    function<void(int)> dfs = [&](int i) {
        if (nodes[i].tin != -1) {
            return;
        }

        nodes[i].tin = t;
        nodes[i].tactive = t;
        nodes[i].inside = true;
        s.push(i);
        deb("in", i, nodes[i].tin, nodes[i].tactive, nodes[i].inside);
        for(auto e : nodes[i].to) {
            t++;
            dfs(e);
            if (nodes[e].inside) {
                nodes[i].tactive = min(nodes[i].tactive, nodes[e].tactive);
                deb("see", i, e, nodes[i].tactive);
            }
        }
        deb("out", i, nodes[i].tin, nodes[i].tactive, nodes[i].inside);

        if (nodes[i].tin == nodes[i].tactive) {
            int cnt=0;
            while(!s.empty()) {
                int e=s.top();
                s.pop();

                ++cnt;
                nodes[e].inside = false;
                if (e == i) {
                    break;
                }
            }
            res=max(res,cnt);
        }
    };

    for(int n=0;n<N;++n) {
        t++;
        dfs(n);
    }

    deb(nodes,res);
    out<<res<<"\n";
}
