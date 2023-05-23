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

fint R,C,J;
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

struct Pole {
    sint missing;
};

constexpr sint NONE = numeric_limits<sint>::max();
struct Sol {
    vector<Pole> poles;
    vector<sint> mem;
    sint completed=0;

    void populate() {
        poles.resize(J);
        mem.resize(R*C,NONE);
        completed = 0;

        queue<pair<sint,sint>> q;
        for(sint j=0;j<J;++j){
            q.push(pair<sint,sint>(castles[j].i, j));
            poles[j].missing = castles[j].size;
        }

        while(!q.empty()){
            sint i,j;
            tie(i,j)=q.front();
            q.pop();

            if (mem[i] != NONE) continue;
            const Castle& castle = castles[j];
            if (grid[i] != 0 && grid[i] != castle.size) continue;
            Pole& pole = poles[j];
            if (pole.missing == 0) continue;
            for_neighbors(i, neigh, if (mem[neigh] != NONE && mem[neigh] != j && castles[mem[neigh]].size == castle.size) continue;)

            pole.missing -= 1;
            if (pole.missing == 0) {
                completed += castle.size;
            }
            mem[i] = j;

            for_neighbors(i, neigh, {
                if (mem[neigh] == NONE && pole.missing != 0) {
                    q.push(pair<sint,sint>(neigh, j));
                }
            })
        }

        // deb("INITIAL!!");
        // for(auto pole:poles)deb(pole.missing);
        // debprint();
    }

    void deletePole() {
        int j=rand()%J;
        const Castle& castle = castles[j];
        Pole& pole = poles[j];
        if(pole.missing == NONE) return;

        // deb("Deleting", j);
        // debprint();

        queue<sint> q;
        map<sint,sint> conn;
        q.push(castles[j].i);
        while(!q.empty()){
            int i=q.front();
            q.pop();
            if (mem[i]!=j) {
                if (grid[i]==0 && mem[i]!=NONE) {
                    for_neighbors(i, neigh, {
                        if(mem[neigh]==NONE){
                            conn[mem[i]]=neigh;
                        }
                    })
                }
                continue;
            }
            mem[i]=NONE;
            for_neighbors(i, neigh, q.push(neigh);)
        }

        /*vector<pair<sint,sint>> conn2;
        conn2.insert(conn2.begin(), conn.begin(), conn.end());
        random_shuffle(conn2.begin(), conn2.end()/*, [&](const pair<sint,sint>& a, const pair<sint,sint>& b) {
            return poles[a.first].missing > poles[b.first].missing;
        );*/

        for(pair<sint,sint> con : conn){
            int jj,ii;
            tie(jj,ii)=con;
            const Castle& castle2 = castles[jj];
            Pole& pole2 = poles[jj];
            // deb("Expanding", jj, ii, pole2.missing);

            q.push(ii);
            while(!q.empty()) {
                int i=q.front();
                q.pop();
                if (mem[i] != NONE) continue;
                if (grid[i] != 0 && grid[i] != castle2.size) continue;
                if (pole2.missing == 0) continue;
                for_neighbors(i, neigh, if (mem[neigh] != NONE && mem[neigh] != jj && castles[mem[neigh]].size == castle2.size) continue;)

                pole2.missing -= 1;
                if (pole2.missing == 0) {
                    completed += castle2.size;
                }
                mem[i] = jj;

                for_neighbors(i, neigh, {
                    if (mem[neigh] == NONE && pole2.missing != 0) {
                        q.push(neigh);
                    }
                })
            }
        }

        if (pole.missing == 0) completed -= castle.size;
        pole.missing = NONE;
        // debprint();
        // deb("Deleted", j, "\n");
    }

    void readdPole() {
        int j=rand()%J;
        for(int jj=j;jj!=j+J;++jj){
            if(poles[jj%J].missing == NONE) {
                j=jj%J;
                break;
            }
        }
        if(poles[j].missing != NONE) return;

        // deb("Readding", j);
        // debprint();

        queue<sint> q;
        q.push(castles[j].i);
        poles[j].missing = castles[j].size;
        while(!q.empty()){
            sint i=q.front();
            q.pop();

            if (mem[i] != NONE) continue;
            const Castle& castle = castles[j];
            if (grid[i] != 0 && grid[i] != castle.size) continue;
            Pole& pole = poles[j];
            if (pole.missing == 0) continue;
            for_neighbors(i, neigh, if (mem[neigh] != NONE && mem[neigh] != j && castles[mem[neigh]].size == castle.size) continue;)

            pole.missing -= 1;
            if (pole.missing == 0) {
                completed += castle.size;
            }
            mem[i] = j;

            for_neighbors(i, neigh, {
                if (mem[neigh] == NONE && pole.missing != 0) {
                    q.push(neigh);
                }
            })
        }

        // debprint();
        // deb("Readded", j, "\n");
    }

    void print() const {
        for(fint i=0;i<R*C;++i){
            if (mem[i] != NONE && poles[mem[i]].missing == 0) {
                out<<castles[mem[i]].size;
            } else {
                out<<'0';
            }
            if(i%C==C-1){
                out<<"\n";
            } else {
                out<<" ";
            }
        }
        out<<"***"<<endl;
    }

    void debprint() const {
    #ifdef DEBUG
        for(fint i=0;i<R*C;++i){
            cerr<<setw(2);
            if (mem[i]==NONE){
                cerr<<-1;
            } else {
                cerr<<mem[i];
            }
            if(i%C==C-1){
                cerr<<"\n";
            } else {
                cerr<<" ";
            }
        }
        cerr<<"*** ("<<completed<<")"<<endl;
    #endif
    }
};

vector<Sol> sols;
void setupTimeLimit(){
    struct sigaction new_action;
    new_action.sa_handler = [](int) {
        int besti=0, bestt=0;
        for(size_t i=0;i<sols.size();++i){
            sols[i].readdPole();
            if(sols[i].completed>bestt){
                bestt=sols[i].completed;
                besti=i;
            }
        }
        deb(bestt);
        sols[besti].print();
        quick_exit(0);
    };
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGXCPU);
    new_action.sa_flags = 0;
    sigaction(SIGXCPU,&new_action,NULL);

    struct rlimit limit;
    getrlimit(RLIMIT_CPU, &limit);
    limit.rlim_cur = 1;
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
    J = castles.size();
    deb("Castles:", J);

    Sol baseline;
    baseline.populate();
    sols.resize(max((size_t)2, (size_t)20000/R/C),baseline);
    deb("Done populating");

    while(true){
        int s=rand()%sols.size();
        Sol newSol=sols[s];
        int K=1+(rand()%6);
        for(int k=0;k<K;++k){
            if(rand() > RAND_MAX/3) {
                newSol.deletePole();
            } else {
                newSol.readdPole();
            }
        }

        int s1=rand()%sols.size();
        if(newSol.completed>=sols[s1].completed || rand() < RAND_MAX/max((int)5, (int)30-(int)sols.size())){
            sols[s1]=newSol;
        }
    }

    return 0;
}
