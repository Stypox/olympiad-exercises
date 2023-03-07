#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Player {
    set<int> completed;
    int points=0, id, t=0;
};

struct Answer {
    string flag;
    int points;
};

struct Submission {
    int m, n, t;
    string flag;
};

signed main() {
    int M,N,S;
    cin>>M>>N>>S;

    vector<Answer> tasks(N);
    vector<Player> players(M);
    vector<Submission> subs(S);
    for(int m=0;m<M;++m){
        players[m].id=m+1;
    }
    for(int n=0;n<N;++n){
        int tmp;
        cin>>tmp>>tasks[n].flag>>tasks[n].points;
    }

    for(int s=0;s<S;++s){
        cin>>subs[s].m>>subs[s].n>>subs[s].flag>>subs[s].t;
        subs[s].m--;subs[s].n--;
    }

    sort(subs.begin(), subs.end(), [](const Submission& a, const Submission& b) {
        return a.t < b.t;
    });

    for(auto&&sub:subs){
        if(sub.flag==tasks[sub.n].flag && !players[sub.m].completed.contains(sub.n)){
            players[sub.m].points+=tasks[sub.n].points;
            players[sub.m].completed.insert(sub.n);
            players[sub.m].t=max(players[sub.m].t,sub.t);
        }
    }

    sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.points != b.points ? a.points > b.points
            : a.t != b.t ? a.t < b.t
            : a.id < b.id;
    });

    for (auto&& player:players){
        cout<<player.id<<" "<<player.points<<"\n";
    }
}
