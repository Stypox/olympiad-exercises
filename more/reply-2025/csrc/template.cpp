#include <cstdint>
#include <deque>
#include <queue>
#include <vector>
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define int int64_t
#define uint uint64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define out cout
#define in cin
#define tdeb(...)

#define INVALID_RES_TYPE -2
#define TOO_MANY_ACQUIRED_RESOURCES -3



enum class ResourceType {
    // Smart Meter - increases # of buildings powered by facilities by a %
    A,
    // Distribution Facility - increases by a % the minimum (Turn_M) and
    // maximum (Turn_X) thresholds of buildings that can be powered
    B,
    // Maintenance Plan - extends by a % the life (Resource_L) of all
    // resources
    C,
    // Renewable Plant - increases by a % the profit per building served
    // (Turn_R)
    D,
    // Accumulator - accumula carica
    E,
    // Base Resource - non fa niente
    X,
};
ostream&operator<<(ostream&o,const ResourceType&p){
    switch(p){
        case ResourceType::A: o << "RT:A"; break;
        case ResourceType::B: o << "RT:B"; break;
        case ResourceType::C: o << "RT:C"; break;
        case ResourceType::D: o << "RT:D"; break;
        case ResourceType::E: o << "RT:E"; break;
        case ResourceType::X: o << "RT:X"; break;
    }
    return o;
}

struct Resource {
    // Resource identifier
    int I;
    // Activation cost (one-time initial expenditure)
    int A;
    // Periodic cost for each turn of life (maintenance expense)
    int P;
    // Number of consecutive turns in which the resource is active
    // and generates profit
    int W;
    // Number of downtime turns required after a full cycle of
    // activity (maintenance)
    int M;
    // Total life cycle of the resource (in turns), including both
    // active and downtime periods, after which the resource becomes
    // obsolete
    int L;
    // Number of buildings the resource can power in each active turn
    int U;
    // Special effect of the resource
    ResourceType T;
    // % of the special effect, the battery capacity, or nothing
    int E;
};
ostream&operator<<(ostream&o,const Resource&p){
    o<<"Res{I="<<p.I<<",A="<<p.A<<",P="<<p.P<<",W="<<p.W<<",M="<<
        p.M<<",L="<<p.L<<",U="<<p.U<<",T="<<p.T<<",E="<<p.E<<"}";
    return o;
}

struct Turn {
    // minimum number of buildings to be powered in that turn
    int M;
    // maximum number of buildings that can be powered in that turn
    int X;
    // profit for each powered building in that turn
    int R;
};
ostream&operator<<(ostream&o,const Turn&p){
    o<<"Turn{M="<<p.M<<",X="<<p.X<<",R="<<p.R<<"}";
    return o;
}



/**
 * @param D initial capital availability
 * @return vector<vector<int>> for each turn (in order), the list of resources acquired
 */
vector<vector<int>> solve(int D, vector<Resource>& resources,
    vector<Turn>& turns, vector<vector<int>> init);



volatile bool ctrlc = false;
void my_handler(signed){
    ctrlc = true;
}

#ifndef RUST1
signed main(int argc, char const* argv[]) {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    int D, R, T;
    in >> D >> R >> T;

    int vret=0;

    vector<Resource> resources;
    bool ip1=false;
    for (int i=0;i<R;++i){
        string line;
        getline(in, line);
        if (i==0 && line.size() < 4) {
            getline(in, line);
        }
        stringstream ss(line);

        Resource r;
        string rt;
        ss >> r.I >> r.A >> r.P >> r.W >> r.M >> r.L >> r.U >> rt >> r.E;
        if (i==0&&r.I==1){
            ip1=true;
        }
        if (ip1) {
            r.I--;
        }
        if (rt == "A") {
            r.T = ResourceType::A;
        } else if (rt == "B") {
            r.T = ResourceType::B;
        } else if (rt == "C") {
            r.T = ResourceType::C;
        } else if (rt == "D") {
            r.T = ResourceType::D;
        } else if (rt == "E") {
            r.T = ResourceType::E;
        } else if (rt == "X") {
            r.T = ResourceType::X;
        } else {
            cerr << "Invalid resource type " << rt << "\n";
            vret = INVALID_RES_TYPE;
        }

        resources.push_back(r);
    }

    vector<Turn> turns;
    for (int i=0;i<T;++i){
        Turn r;
        in >> r.M>>r.X>>r.R;
        turns.push_back(r);
    }

    vector<vector<int>> init(turns.size());
    if (argc > 1) {
        ifstream f{argv[1]};
        while (f) {
            int t,c;
            f>>t>>c;
            if (!f||f.eof()) break;
            for(int cc=0;cc<c;++cc){
                int a;
                f>>a;
                a-=ip1;
                init[t].push_back(a);
            }
        }
    }

    vector<vector<int>> result = solve(D, resources, turns, init);

    int i=0;
    for (vector<int>& turn : result) {
        i++;
        if (turn.size() == 0) {
            continue;
        }
        out << i-1 << " " << turn.size();
        if (turn.size() > 50) {
            cerr << "Too many acquired resources " << turn.size() << " in result " << i << "\n";
            vret = TOO_MANY_ACQUIRED_RESOURCES;
        }
        for (int ri : turn) {
            out << " " << ri+ip1;
        }
        out << "\n";
    }

    return vret;
}

int apply_percentage(int value, int percentage) {
    return max(value * (percentage + 100) / 100, (int)0);
}

pair<int64_t, vector<int>> eval(int initial_budget, vector<Resource>& resources, vector<Turn>& turns, vector<vector<int>> out){
    /*if(turns.size()!=out.size()){
        return -6;
    }*/
    int64_t budget = initial_budget;
    int score = 0;
    vector<int> profitti;

    vector<multiset<pair<uint64_t, int64_t>>> bought(resources.size(), multiset<pair<uint64_t, int64_t>>());
    

    ///total maintenece cost
    int64_t total_rp=0;
    //set lifetime
    int64_t charge=0;
    for(uint i=0; i<out.size(); i++){
        tdeb("\n", i, "charge", charge, "total_rp", total_rp, "budget", budget);
        if(out[i].size()>50){
            return {-7, {}};
        }

        ///clean exausted resources
        for(uint b=0; b<bought.size(); b++){
            for (auto it{bought[b].begin()}, end{bought[b].end()}; it != end; ) {
                if ((*it).first <= i) {
                    it = bought[b].erase(it);
                    total_rp-=resources[b].P;
                } else {
                    ++it;
                }
            }
        }
        int64_t A=0, B=0, C=0, D=0, E=0;
        
        /// start of turn
        int64_t turn_cost=0;
        int64_t to_add_rp =0;
        for (uint b=0; b<out[i].size(); b++){
            uint index = out[i][b];
            tdeb(resources[index]);
            if(index<0||index>=resources.size()){
                deb("ERRORE INDICE NVALID", index);
                return {-4, {}};
            }
            turn_cost += resources[index].A;
            to_add_rp += resources[index].P;
            /// add the effect if C type
            if(resources[index].W>0){
                switch (resources[index].T){
                    case ResourceType::A:
                        A += resources[index].E;
                        break;
                    case ResourceType::B:
                        B += resources[index].E;
                        break;
                    case ResourceType::C:
                        C += resources[index].E;
                        break;
                    case ResourceType::E:
                        E += resources[index].E;
                        break;
                    case ResourceType::D:
                        D += resources[index].E;
                        break;
                    case ResourceType::X:
                        break;
                }
            }
        }

        if(turn_cost>budget){
            profitti.push_back(0);
            tdeb("continue");
            continue;
        }
        total_rp+=to_add_rp;
        /// apply periodic cost:
        budget -=turn_cost+total_rp;


        /// compute effects
        for(uint b=0; b<bought.size(); b++){
            for( auto it=bought[b].begin(); it!=bought[b].end(); it++){
                uint resource_len = resources[b].W+resources[b].M;
                if((i-it->second)%resource_len<(uint)resources[b].W){
                    switch (resources[b].T){
                        case ResourceType::A:
                            A += resources[b].E;
                            break;
                        case ResourceType::B:
                            B += resources[b].E;
                            break;
                        case ResourceType::C:
                            C += resources[b].E;
                            break;
                        case ResourceType::E:
                            E += resources[b].E;
                            break;
                        case ResourceType::D:
                            D += resources[b].E;
                            break;
                        case ResourceType::X:
                          break;
                        }
                    }
            }
        }

        /// add to bought elements
        for (uint b=0; b<out[i].size(); b++){
            int index = out[i][b];
            bought[index].insert({i+apply_percentage(resources[index].L, C), i});
        }

        /// apply effect and compute profit
        int64_t powered_buildings = 0;
        for(uint b=0; b<bought.size(); b++){
            for( auto it=bought[b].begin(); it!=bought[b].end(); it++){
                uint resource_len = resources[b].W+resources[b].M;
                if((i-it->second)%resource_len<(uint)resources[b].W){
                    powered_buildings+=apply_percentage(resources[b].U, A);
                }
            }
        }

        int64_t tm = apply_percentage(turns[i].M, B);
        int64_t tx = apply_percentage(turns[i].X, B);
        if (powered_buildings>=tm){
            charge+=powered_buildings-tm;
        }
        /// TODO WTF
        if(charge>E){
            charge=E;
        }
        if (powered_buildings<tm && charge>=tm-powered_buildings){
            powered_buildings=tm;
            charge-=tm-powered_buildings;
        }
        
        int64_t profit =0;
        if (powered_buildings>=tm){
            profit = min(powered_buildings, tx)*apply_percentage(turns[i].R, D);
        }
        budget+=profit;
        score+=profit;
        tdeb(budget, profit, powered_buildings,tm,tx);
        tdeb(bought);
        profitti.push_back(profit);
    }
    return {score, profitti};
}

#endif
