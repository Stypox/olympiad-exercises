#pragma GCC optimize ("O3")
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

struct Node {
    vector<pair<int,bool>> shortest;
    bool ours=false;
};

struct Con {
    int a,b,c;
};

struct Interval {
    int x0, q, m;
    bool ours;
};

#ifdef DEBUG
ostream&operator<<(ostream&o,const Interval&p){cerr<<"(x0="<<p.x0<<", q="<<p.q<<", m="<<p.m<<", ours="<<p.ours<<")";return o;}
#endif

signed main() {
    int N,P,X,Y;
    cin>>N>>P>>X>>Y;
    X--; Y--;

    vector<Node> nodes(N);
    vector<Con> cons(P);

    for(int p=0;p<P;++p){
        cin>>cons[p].a>>cons[p].b>>cons[p].c;
        cons[p].a--; cons[p].b--;
    }

    int M;
    cin>>M;
    for(int m=0;m<M;++m){
        int a;
        cin>>a;
        a--;
        nodes[a].ours=true;
    }

    for(int n=0;n<N;++n){
        nodes[n].shortest.resize(N+1, {numeric_limits<int>::max(), nodes[n].ours});
    }

    // Calculate shortest paths of length 1..N, i.e. calculate q for all m in 1..N (see below).
    // This is O(N*P).
    nodes[X].shortest[0] = {0, true};
    for (int n=1;n<=N;++n) {
        for (auto& [tmpa,tmpb,c] : cons) {
            for (auto& [a,b] : initializer_list<pair<int,int>>{{tmpa,tmpb}, {tmpb, tmpa}}) {
                pair<int,bool> shortest = nodes[b].shortest[n-1];
                if (shortest.first != numeric_limits<int>::max()) {
                    shortest.first += c;
                }
                shortest.second = shortest.second && nodes[a].ours;

                // comparison between pairs, so if the the path length (i.e. first) is equal,
                // then it checks whether the new path is using any competitor (i.e. second)
                // and if that's the case it still updates the shortest to favour competitors
                if (shortest < nodes[a].shortest[n]) {
                    nodes[a].shortest[n] = shortest;
                }
            }
        }

        deb(n, nodes[Y].shortest[n]);
    }

    // The shortest path of length m has the weight q calculated above,
    // and represents a line y=mx+q, where x is the fee and y is the cost of the path.
    // So here we find for each possible fee (x), which of these equations has the
    // minimum cost (y) by intersecting the lines efficiently.
    // This is O(n) since every line is added or removed from the intervals list at most
    // once.
    vector<Interval> intervals{
        Interval{-2, (N+2)*1'000'000'000LL, 2*N+2*2, false},
    };
    for (int m=N;m>0;--m){
        auto [q, ours] = nodes[Y].shortest[m];
        if (q == numeric_limits<int>::max()) {
            continue;
        }

        while (true) {
            // y=m*x+q and y=im*x+iq => m*x+q=im*x+iq => x0=(iq-q)/(m-im)
            auto [ix0, iq, im, icompetitor] = intervals.back();
            int dm = im - m; // m is surely less than im
            int dq = q - iq;
            int x0 = (dq + (dq > 0 ? (dm-1) : 0))/dm; // round up
            deb(dm, dq, x0);

            if (ix0 >= x0) {
                intervals.pop_back();
            }

            if (ix0 < x0 || intervals.size() == 0) {
                intervals.push_back(Interval{x0, q, m, ours});
                break;
            }
        }

        deb(q, m, ours, intervals);
    }

    if (intervals.back().ours) {
        cout<<"Infinity\n";
    } else {
        bool found = false;
        for(int i=intervals.size()-1; i>0; --i){
            if (intervals[i-1].ours && intervals[i].x0 > 1) {
                found = true;
                cout << intervals[i].x0-1 << "\n";
                break;
            }
        }

        if (!found) {
            cout<<"Impossible\n";
        }
    }
}
