#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Player {
    vector<short> scores;
    bool used=false;
};

signed main() {
    int T;
    cin>>T;
    for(int t=0;t<T;++t){
        cerr<<t<<"\n";
        int N,M,S;
        cin>>N>>M>>S;

        map<string,short> sm;
        auto readNewSkill = [&]() {
            string s;
            cin>>s;
            if (!sm.contains(s)) {
                sm[s] = sm.size();
            }
            return sm[s];
        };

        vector<short> wanted(M);
        for(int m=0;m<M;++m){
            wanted[m]=readNewSkill();
        }

        deb(wanted);

        vector<Player> players(N);
        for(int n=0;n<N;++n){
            int tmp;
            cin>>tmp;
            players[n].scores.resize(sm.size());
            for(int s=0;s<S;++s){
                string v;
                short score;
                cin>>v>>score;
                if (sm.contains(v)) {
                    players[n].scores[sm[v]] = score;
                }
            }
        }

        vector<vector<int>> wantedPs(sm.size());
        for(int s=0;s<sm.size();++s) {
            vector<pair<int,int>> r;
            for(int n=0;n<N;++n){
                r.emplace_back(-players[n].scores[s], n);
            }

            sort(r.begin(), r.end());
            for(int n=0;n<N&&n<M;++n){
                wantedPs[s].push_back(r[n].second);
            }
        }

        auto bestPlayers = [&]() {
            set<int> ps;
            for(int s=0;s<sm.size();++s) {
                for(auto&&p:wantedPs[s]){
                    if(!players[p].used){
                        ps.insert(p);
                        break;
                    }
                }
            }
            return ps;
        };

    #ifdef DEBUG
        vector<int> trace;
        function<int(int,bool)> rec = [&](int m, bool print) -> int {
    #else
        function<int(int)> rec = [&](int m) -> int {
    #endif
            if (m == M) {
                return 0;
            }

        #ifdef DEBUG
            int res=rec(m+1, false);
            int bestp=-1;
        #else
            int res=rec(m+1);
        #endif
            for (auto& p : bestPlayers()) {
                players[p].used = true;
                int recres = players[p].scores[wanted[m]] +
                #ifdef DEBUG
                    rec(m+1, false);
                if (recres > res) {
                    res=recres;
                    bestp=p;
                }
                #else
                    rec(m+1);
                res=max(res,recres);
                #endif
                players[p].used = false;
            }

        #ifdef DEBUG
            if (print) {
                trace.push_back(bestp+1);
                if (bestp != -1) players[bestp].used = true;
                rec(m+1, true);
                if (bestp != -1) players[bestp].used = false;
            }
        #endif
            return res;
        };

    #ifdef DEBUG
        cout<<rec(0,true)<<"\n";
        deb(trace);
    #else
        cout<<rec(0)<<"\n";
    #endif
    }
}
