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

        if(t!=TTOCONSIDER){
            continue;
        }
        cerr<<t<<" "<<TTOCONSIDER<<"\n";

        vector<int> wantedXs(sm.size(),0);
        vector<vector<int>> wantedPs(sm.size());
        for(int s=0;s<sm.size();++s) {
            vector<pair<int,int>> r;
            for(int n=0;n<N;++n){
                r.emplace_back(-players[n].scores[s], n);
            }

            sort(r.begin(), r.end());
            for(int n=0;n<N&&n<M;++n){
                if (r[n].first != 0) {
                    wantedPs[s].push_back(r[n].second);
                }
            }
        }

        function<int(int)> rec = [&wantedPs,&players,&wanted,M,&rec,&wantedXs](int m) -> int {
            if (m == M) {
                return 0;
            }

            int res=rec(m+1);
            int prevWantedXs=wantedXs[wanted[m]];
            int iterCount=min(wantedPs[wanted[m]].size(), (size_t)M-m+prevWantedXs+1);
            for(size_t x=prevWantedXs;x<iterCount;++x){
                int p=wantedPs[wanted[m]][x];
                if (!players[p].used) {
                    players[p].used=true;
                    wantedXs[wanted[m]]=x+1;
                    res=max(res, players[p].scores[wanted[m]] + rec(m+1));
                    wantedXs[wanted[m]]=prevWantedXs;
                    players[p].used=false;
                }
            }

            return res;
        };

        cout<<rec(0)<<"\n";
        cerr<<t<<" finished\n";
    }
}
