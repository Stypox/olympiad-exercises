#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "alpini.h"
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

int N,M;
vector<vector<int>> graph;

struct Node {
    int parent;
    int rank = 1;
    bool used = false;
};

struct Sol {
    int usedCount = 0;
    vector<Node> nodes;

    Sol() : nodes(N) {
        for (int n=0;n<N;n++){
            nodes[n].parent = n;
        }
    }

    int groupOf(int i) {
        if (nodes[i].parent == i) {
            return i;
        }
        return nodes[i].parent = groupOf(nodes[i].parent);
    }

    void mergeGroupsOf(int i, int j) {
        int ri = groupOf(i);
        int rj = groupOf(j);

        if (nodes[rj].rank > nodes[ri].rank) {
            swap(ri, rj);
        }
        // ri now has the highest rank

        nodes[rj].parent = ri;
        nodes[ri].rank = max(nodes[ri].rank, nodes[rj].rank+1);
    }

    pair<bool, set<int>> canAdd(int n) {
        if (nodes[n].used) {
            return make_pair<bool, set<int>>(false, set<int>());
        }

        set<int> groups;
        for(auto e:graph[n]) {
            if (nodes[e].used) {
                int group = groupOf(e);
                if (groups.count(group)) {
                    return make_pair<bool, set<int>>(false, set<int>());
                }
                groups.insert(group);
            }
        }
        return make_pair<bool, set<int>>(true, move(groups));
    }

    void uncheckedAdd(int n, set<int>&& groups) {
        for(auto g:groups){
            mergeGroupsOf(n, g);
        }
        nodes[n].used = true;
        ++usedCount;
    }

    void print() {
        out<<N-usedCount<<" ";
        for(int n=0;n<N;++n) {
            if (!nodes[n].used) {
                out<<n<<" ";
            }
        }
        out<<"#"<<endl;
    }
};

signed main() {
    in>>N>>M;
    graph.resize(N);
    for(int m=0; m<M; ++m){
        int a,b;
        in>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int bestUsedCount = 0;
    vector<Sol> sols(N*N);
    while(true){
        int s = rand() % sols.size();
        int n = rand() % N;
        bool ok;
        set<int> groups;
        tie(ok, groups) = sols[s].canAdd(n);

        if (ok) {
            Sol newSol = sols[s];
            newSol.uncheckedAdd(n, move(groups));

            s = rand() % sols.size();
            if (newSol.usedCount >= sols[s].usedCount) {
                sols[s] = newSol;
                if (newSol.usedCount > bestUsedCount) {
                    bestUsedCount = newSol.usedCount;
                    newSol.print();
                }
            }
        }
    }

    return 0;
}
