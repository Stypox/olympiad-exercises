#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "tsp.h"
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

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> randomNode, randomSol;
std::uniform_real_distribution<float> randomFloat(0, 1);

struct Node {
    vector<int> w;
    bool vis=false;
};
int N;
vector<Node> nodes;

struct Sol {
    vector<int> path;
    int length;

    Sol createPermutation() {
        Sol sol = *this;
        int a = randomNode(rng);
        int b = randomNode(rng);
        sol.length -= nodes[sol.path[a-1]].w[sol.path[a]] + nodes[sol.path[a]].w[sol.path[a+1]] + nodes[sol.path[b-1]].w[sol.path[b]] + nodes[sol.path[b]].w[sol.path[b+1]];
        swap(sol.path[a], sol.path[b]);
        sol.length += nodes[sol.path[a-1]].w[sol.path[a]] + nodes[sol.path[a]].w[sol.path[a+1]] + nodes[sol.path[b-1]].w[sol.path[b]] + nodes[sol.path[b]].w[sol.path[b+1]];
        return sol;
    }

    void print() {
        for(int n=0;n<N+1;++n){
            if(n!=0)out<<" ";
            out<<path[n];
        }
        out<<"#\n"<<flush;
    }
};

Sol getInitialSol() {
    int cost=0;
    vector<int> path{0};

    int cur=0;
    nodes[cur].vis=true;
    for(int n=0;n<N-3;++n) {
        int bestV=numeric_limits<int>::max();
        int bestA=-1;
        for(int a=0;a<N;++a){
            if (nodes[a].vis) continue;
            int v = nodes[cur].w[a];
            if (v < bestV) {
                bestV=v;
                bestA=a;
            }
        }
        cost+=nodes[cur].w[bestA];
        cur=bestA;
        nodes[cur].vis=true;
        path.push_back(cur);
    }


    int bestV=numeric_limits<int>::max();
    int bestA=-1, bestB=-1;
    for(int a=0;a<N;++a){
        if (nodes[a].vis) continue;
        for(int b=0;b<N;++b){
            if (nodes[b].vis || a==b) continue;
            int v = nodes[cur].w[a] + nodes[a].w[b] + nodes[b].w[0];
            if (v < bestV) {
                bestV=v;
                bestA=a;
                bestB=b;
            }
        }
    }

    cost += bestV;
    path.push_back(bestA);
    path.push_back(bestB);
    path.push_back(0);

    return Sol{path, cost};
}

signed main() {
    in>>N;
    randomNode = std::uniform_int_distribution<std::mt19937::result_type>(1, N-1);
    randomSol = std::uniform_int_distribution<std::mt19937::result_type>(0, N*N-1);
    nodes.resize(N);
    for(auto&& node:nodes) node.w.resize(N);

    for(int n=1;n<N;++n){
        for(int m=0;m<n;++m){
            int w;
            in>>w;
            nodes[n].w[m] = w;
            nodes[m].w[n] = w;
        }
    }

    Sol initialSol = getInitialSol();
    initialSol.print();
    int bestLength = initialSol.length;
    vector<Sol> sols(N*N, initialSol);
    while (true) {
        int s=randomSol(rng);
        Sol newSol = sols[s].createPermutation();
        for (int k=0; k<randomNode(rng)-1; ++k) {
            newSol = newSol.createPermutation();
        }
        if (newSol.length < bestLength) {
            newSol.print();
            bestLength = newSol.length;
            deb(bestLength);
        }
        if (newSol.length <= sols[s].length || randomFloat(rng) < exp(10 * (sols[s].length - newSol.length) / bestLength)) {
            sols[s] = newSol;
        }
    }
    return 0;
}
