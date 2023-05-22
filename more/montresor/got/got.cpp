#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "got.h"
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";if(distance(v.begin(), it) % 5 == 0)cout<<"\n ";}cout<<setw(2)<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define cout Do not use cout!!!
#define cin Do not use cin!!!

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

signed main() {
    in>>R>>C;
    grid.resize(R*C);
    for(fint i=0;i<R*C;++i){
        in>>grid[i];
        if (grid[i]!=0){
            castles.push_back(Castle{(sint)i,grid[i]});
        }
    }
    sort(castles.begin(), castles.end());

    for(int i=0;i<R*C;++i){
        for(int j=0;j<R*C;++j){
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
    }

    vector<Sol> sols(min((size_t)1024*1024/R/C, (size_t)1000));
    fint bestTaken=sols[0].taken;
    auto onFoundSol = [&](Sol& newSol){
        if(newSol.taken>bestTaken){
            newSol.print();
            bestTaken=newSol.taken;
        }
        for(int j=0;j<5;++j){
            fint si=rand()%sols.size();
            if(newSol.taken >= sols[si].taken){
                sols[si] = newSol;
            }
        }
    };

    vector<sint> used(R*C,0);
    vector<fbint> points(R*C);
    sint usedi=1;

    while(true){
        fint si=rand()%sols.size();
        const Sol& sol = sols[si];
        const auto& mem = sol.mem;

        fint ci=rand()%min((int)sol.usableCastles.size(),max((int)castles.size()/10,(int)20));
        auto cit=sol.usableCastles.begin();
        advance(cit, ci); // TODO optimizable
        const Castle& cas = castles[*cit];

        fint touchedCastlesSoFar=0;
        fint oneTouchedCastle=0; // chooses one random castle among touched ones
        vector<fint> q;
        q.push_back(cas.i);
        used[cas.i]=usedi;
        points[cas.i]=0;

        for(int qi=0; qi!=q.size(); ++qi){
            fint i=q[qi];
            fint dist = manh_dist(i, cas.i);

            for_neighbors(i, neigh, {
                points[neigh]=0;
                if (mem[neigh]!=0){
                    if (rand()%(touchedCastlesSoFar+1)==0){
                        oneTouchedCastle=neigh;
                        touchedCastlesSoFar+=1;
                    }
                } else if (dist<cas.size-1 && (grid[neigh]==0||grid[neigh]==cas.size) && used[neigh]!=usedi) {
                    bool foundbadneighbor=false;
                    for_neighbors(neigh, neigh2, {
                        if(mem[neigh2]==cas.size){
                            foundbadneighbor = true;
                        }
                    })
                    if (!foundbadneighbor) {
                        used[neigh]=usedi;
                        q.push_back(neigh);
                    }
                }
            })
        }

        for(int qi=q.size()-1; qi>=0; --qi){
            fint i=q[qi];
            for_neighbors(i, neigh, {
                if(mem[neigh]==cas.size){
                    continue;
                }
            })
            fint dist = manh_dist(i, cas.i);

            int p=1;
            if(grid[i]==cas.size){
                p+=2;
            }
            int neighCount=0;
            int neighSum=0;
            for_neighbors(i, neigh, {
                if (manh_dist(neigh, cas.i) > dist) {
                    if (mem[neigh]!=0){
                        p+=1;
                    } else if(points[neigh]!=0) {
                        neighCount+=1;
                        neighSum+=points[neigh];
                    }
                }
            })
            if(neighCount!=0){
                p+=(neighSum+neighCount-1)/neighCount;
            }
            points[i]=p;
            if (points[i]==0){
                deb("Lo sto mettendo a zero");
            }
        }

        if(points[cas.i]!=0 && q.size()>=cas.size){
            Sol newSolFill = sol;
            priority_queue<pair<fbint,fint>> pq;
            pq.push(pair<fbint,fint>(0,cas.i));
            int toFill=cas.size;

            auto prevPoints=points;
            while(toFill>0){
                if(pq.empty()){
                    sol.debprint();
                    newSolFill.debprint();
                    deb(points);
                    deb(prevPoints);
                    deb(used);
                    deb(usedi,cas.i,cas.size,q.size(),q);
                    deb(manh_dist(43,44), manh_dist(35,31), manh_dist(35,41), manh_dist(44,43), manh_dist(31,35), manh_dist(41,35));
                    assert(false);
                }
                fint i=pq.top().second;
                pq.pop();
                if(points[i]==0) continue;
                toFill--;

                assert(newSolFill.mem[i]==0);
                assert(grid[i]==0 || grid[i]==cas.size);
                newSolFill.mem[i]=cas.size;
                for_neighbors(i, neigh, {
                    if (points[neigh]!=0){
                        pq.push(pair<fbint,fint>(points[neigh],neigh));
                    }
                })
                points[i]=0;
            }

            newSolFill.taken += cas.size;
            newSolFill.usableCastles.erase(cas.i);
            onFoundSol(newSolFill);
            //newSolFill.debprint();

        }else if(touchedCastlesSoFar!=0&&q.size()+sol.mem[oneTouchedCastle]>=cas.size){

        }

        usedi+=1; // let it overflow
        if(usedi==0 ||
            #ifdef DEBUG
                true
            #else
                false
            #endif
        ){
            usedi+=1;
            fill(used.begin(),used.end(),0);
        }

        //if(cas.size == 9)break;
    }

    return 0;
}
