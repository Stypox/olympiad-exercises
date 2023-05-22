#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
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

using sint = uint16_t; // small int
using fint = uint_fast16_t; // fast int
using fbint = uint_fast32_t; // fast big int

fint R,C;
vector<sint> grid;

#define for_neighbors(i, var_name, code) \
    if (i%C != 0)   { fint var_name=i-1; code } \
    if (i%C != C-1) { fint var_name=i+1; code } \
    if (i/C != 0)   { fint var_name=i-C; code } \
    if (i/C != R-1) { fint var_name=i+C; code }

#define manh_dist(i, j) \
    (((i > j) ? (i / C - j / C) : (j / C - i / C)) \
    + ((i % C > j % C) ? (i % C - j % C) : (j % C - i % C)))

struct Castle {
    sint i, size;

    bool operator<(const Castle& other) const {
        return size < other.size;
    }
};
vector<Castle> castles;

struct Sol {
    vector<sint> mem;
    set<sint> usableCastles;
    sint taken=0;

    Sol() : mem(R*C,0) {
        // initializes a solution that just takes all 1s available
        for(fint i=0;i<R*C;++i){
            if(grid[i]==1){
                for_neighbors(i, neigh, if(mem[neigh]!=0) break;)
                mem[i]=1;
                taken+=1;
            }
        }

        for(fint j=0;j<castles.size();++j){
            if(castles[j].size!=1){
                usableCastles.insert(j);
            }
        }
    }

    void print() const {
        for(fint i=0;i<R*C;++i){
            out<<mem[i];
            if(i%C==C-1){
                out<<"\n";
            } else {
                out<<" ";
            }
        }
        out<<"***"<<endl;
    }

    void debprint() const {
        for(fint i=0;i<R*C;++i){
            cerr<<mem[i];
            if(i%C==C-1){
                cerr<<"\n";
            } else {
                cerr<<" ";
            }
        }
        cerr<<"*** (" << taken << " taken)"<<endl;
    }
};

vector<Sol> sols;
void setupTimeLimit(){
    struct sigaction new_action;
    new_action.sa_handler = [](int signum) {
        int besti, bestt=0;
        for(int i=0;i<sols.size();++i){
            if(sols[i].taken>bestt){
                bestt=sols[i].taken;
                besti=i;
            }
        }
        sols[besti].print();
        quick_exit(0);
    };
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGXCPU);
    new_action.sa_flags = 0;
    sigaction(SIGXCPU,&new_action,NULL);

    struct rlimit limit;
    getrlimit(RLIMIT_CPU, &limit);
    limit.rlim_cur = 2;
    setrlimit(RLIMIT_CPU, &limit);
}

signed main() {
    setupTimeLimit();

    in>>R>>C;
    grid.resize(R*C);
    for(fint i=0;i<R*C;++i){
        in>>grid[i];
        if (grid[i]!=0){
            castles.push_back(Castle{(sint)i,grid[i]});
        }
    }
    sort(castles.begin(), castles.end());
    deb("Castles:",castles.size());

    /*for(fint i=0;i<R*C;++i){
        for(fint j=0;j<R*C;++j){
            if(manh_dist(i,j) != manh_dist(j,i)){
                deb("Different", i, j, manh_dist(i,j), manh_dist(j,i));
                assert(false);
            }
            int d = manh_dist(i,j);
            int ri=i/C;
            int rj=j/C;
            int ci=i%C;
            int cj=j%C;
            if (abs(ri-rj)+abs(ci-cj)!=d) {
                deb("Error", i, j, d, ri, rj, ci, cj, abs(ri-rj)+abs(ci-cj));
                assert(false);
            }
        }
    }*/

    sols.resize(2);
    vector<sint> used(R*C,0);
    vector<sint> buf(4*R*C+1);
    size_t bufb=0,bufe=1;
    sint usedi=1;

    int64_t iter=0;
    while(true){
        fint si=rand()%sols.size();
        Sol& sol = sols[si];
        auto& mem = sol.mem;

        fint ci=rand()%sol.usableCastles.size();
        auto cit=sol.usableCastles.begin();
        advance(cit, ci); // TODO optimizable
        const Castle& cas = castles[*cit];
        for_neighbors(cas.i, neigh, {
            if (mem[neigh]!=0 && mem[neigh]!=cas.size){
                // this castle can't ever be taken since it is near a zone with the same wanted size
                sol.usableCastles.erase(cit);
                continue;
            }
        })

        fint touchedCastlesSoFar=0;
        fint oneTouchedCastle=0; // chooses one random castle among touched ones
        fint usedCount=0;

        bufb=0; bufe=1; buf[0]=cas.i;
        while(bufb!=bufe){
            sint i = buf[bufb++];

            if (used[i] == usedi) continue;
            for_neighbors(i, neigh, if(mem[neigh] == cas.size) continue;)
            if (mem[i] != 0 || !(grid[i]==0 || grid[i]==cas.size) || manh_dist(i, cas.i) >= cas.size) continue;

            used[i] = usedi;
            usedCount += 1;
            for_neighbors(i, neigh, buf[bufe++] = neigh;)
        }

        //deb(usedCount, cas.size);
        if (usedCount>=cas.size) {
            bufb=0; bufe=1; buf[0]=cas.i;
            int toFill=cas.size;
            while(toFill>0){
                sint i = buf[bufb++];

                if (used[i] != usedi) continue;
                used[i] = 0;
                mem[i] = cas.size;

                for_neighbors(i, neigh, buf[bufe++] = neigh;)
                if(rand() < INT_MAX/min(toFill,10)){
                    int a=rand()%(bufe-bufb);
                    int b=rand()%(bufe-bufb);
                    swap(buf[bufb+a], buf[bufb+b]);
                }

                toFill--;
            }

            sol.taken += cas.size;
            sol.usableCastles.erase(cas.i);
        }

        usedi+=1; // let it overflow
        if(usedi==0){
            usedi+=1;
            fill(used.begin(),used.end(),0);
        }

        iter+=1;
        if (iter % ((R+C)*10) == 0 && sols.size() <= min((R+C)/2, 1024*1024/(R*C+R+C+128))) {
            int ssize=sols.size();
            for(int s=0;s<ssize;++s){
                sols.push_back(sols[s]);
            }
            deb("Iter:", iter, "Score:", sols[0].taken);
        }
    }
    return 0;
}
