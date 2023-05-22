#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "got.h"
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

int R,C;
vector<int> grid;

struct UFDS {
    uint16_t par;
    uint16_t remaining = numeric_limits<uint16_t>::max();

    bool hasWantedSize(){
        return remaining==0;
    }

    bool isUsed(int i){
        return par!=i || remaining!=numeric_limits<uint16_t>::max();
    }
};
static_assert(sizeof(UFDS) == 4);

struct Sol {
    vector<UFDS> mem;
    int satisfied=0;

    Sol() : mem(R*C) {
        for(int i=0;i<R*C;++i){
            mem[i].par=i;
        }
    }

    int root(int i) {
        if(mem[i].par==i) return i;
        return mem[i].par = root(mem[i].par);
    }

    void merge(int i, int j) {
        int ri=root(i);
        int rj=root(j);
        if (ri==rj) {
            return;
        }

        // if(mem[rj].remaining>mem[ri].remaining){
        //     swap(ri,rj);
        // }
        // //now ri has the highest size

        mem[ri].remaining-=(grid[rj]-mem[rj].remaining);
        if (mem[ri].hasWantedSize()) {
            satisfied+=grid[ri];
        }
        mem[rj].par=ri;
    }

    void print() {
        for(int i=0;i<R*C;++i){
            if (i!=0) {
                if (i%C==0){
                    out<<"\n";
                } else {
                    out<<" ";
                }
            }
            int ri = root(i);
            if (mem[ri].hasWantedSize()) {
                out<<grid[ri];
            } else {
                out<<0;
            }
        }
        out<<"\n***"<<endl;
    }
#ifdef DEBUG
    void debprint() {
        for(int i=0;i<R*C;++i){
            if (i!=0) {
                if (i%C==0){
                    cerr<<"\n";
                } else {
                    cerr<<" ";
                }
            }
            int ri = root(i);

            if(mem[ri].remaining==numeric_limits<uint16_t>::max()){
                cerr<<"(_,_)";
            } else {
                cerr<<"("<<grid[ri]<<","<<mem[ri].remaining<<")";
            }
        }
        cerr<<"\n***"<<endl;
    }
#else
    inline void debprint() {}
#endif
};

vector<int> neighbors(int i) {
    vector<int> res;
    if (i%C != 0) {
        res.push_back(i-1);
    }
    if (i%C != C-1) {
        res.push_back(i+1);
    }
    if (i/C != 0) {
        res.push_back(i-C);
    }
    if (i/C != R-1) {
        res.push_back(i+C);
    }
    return res;
}

signed main() {
    in>>R>>C;
    grid.resize(R*C);
    for(int i=0;i<R*C;++i){
        in>>grid[i];
    }

    Sol allOnes;
    for(int i=0;i<R*C;++i){
        if(grid[i]==1){
            for(auto neigh:neighbors(i)){
                if(allOnes.mem[neigh].remaining==0) goto skip;
            }
            allOnes.mem[i].remaining=0;
            skip:;
        }
    }

    vector<Sol> sols(min(4*1024*1024/R/C/sizeof(UFDS), (unsigned long)1000), allOnes);
    //sols.resize(1);
    int bestSatisfied=0;
    while(true){
        int s=rand()%(sols.size());
        Sol& sol=sols[s];

        int i=rand()%(R*C);
        if(sol.mem[i].isUsed(i)) {
            continue;
        }

        set<int> seenr;
        map<int,int> sizes;
        for(auto neigh:neighbors(i)) {
            if (sol.mem[neigh].isUsed(neigh)){
                int nr = sol.root(neigh);
                if (seenr.count(nr)) {
                    continue;
                }
                seenr.insert(nr);
                sizes[grid[nr]] += grid[nr] - sol.mem[nr].remaining;
            }
        }

        int bestWantedSize;
        if (grid[i] == 0) {
            // adding an empty cell
            int bestDiff=numeric_limits<int>::max();
            for(const auto& v:sizes){
                if (v.second < v.first && v.first-v.second<bestDiff){
                    bestDiff=v.first-v.second;
                    bestWantedSize=v.first;
                }
            }
            if (bestDiff==numeric_limits<int>::max()) {
                continue;
            }
        } else {
            // adding a cell with a castle
            if(sizes[grid[i]] >= grid[i]) {
                continue;
            }
            bestWantedSize=grid[i];
            sol.mem[i].remaining=grid[i]-1;
        }

        for(auto neigh:neighbors(i)) {
            if (sol.mem[neigh].isUsed(neigh)){
                int nr = sol.root(neigh);
                if(grid[nr]==bestWantedSize){
                    sol.merge(neigh,i);
                }
            }
        }

        //sol.debprint();
        if (sol.satisfied > bestSatisfied) {
            sol.print();
            bestSatisfied = sol.satisfied;
        }
    }

    return 0;
}
