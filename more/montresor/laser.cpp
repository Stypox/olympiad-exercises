#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

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

struct Edge {
    int to,weight,tStart,tOff,tOn;
};

struct Node {
    vector<Edge> to;
    int tMin=numeric_limits<int>::max();
    int prev=-1;
};

signed main() {
    int N,M;
    in>>N>>M;

    vector<Node> nodes(N);
    for(int m=0;m<M;++m){
        int s,t,w,f,y,n;
        in>>s>>t>>w>>f>>y>>n;
        nodes[s].to.push_back(Edge{t,w,f,y,n});
        nodes[t].to.push_back(Edge{s,w,f,y,n});
    }

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq{};
    pq.push({0,0,-1});
    while(!pq.empty()) {
        auto [t,i,prev] = pq.top();
        pq.pop();

        if (t < nodes[i].tMin) {
            nodes[i].tMin = t;
            nodes[i].prev = prev;
            for(auto& e:nodes[i].to){
                int tArrival;
                int eta=t+e.weight;
                if (e.tOff < e.weight) {
                    continue; // edge is not usable
                } else if (t < e.tStart) {
                    tArrival = e.tStart + e.weight;
                } else {
                    int period = e.tOn + e.tOff;
                    int tIter = (t-e.tStart)/period;
                    int tOffset = (t-e.tStart)%period;
                    int etaIter = (eta-e.tStart)/period;
                    int etaOffset = (eta-e.tStart)%period;

                    if (tIter == etaIter && etaOffset <= e.tOff) {
                        tArrival = eta;
                    } else {
                        tArrival = e.tStart + period * (tIter + 1) + e.weight;
                    }
                }
                pq.push({tArrival, e.to, i});
            }
        }
    }

    if (nodes[N-1].tMin == numeric_limits<int>::max()) {
        out << -1 << "\n";
    } else {
        out << nodes[N-1].tMin << "\n";

        vector<int> path{N-1};
        while (nodes[path.back()].prev != -1) {
            path.push_back(nodes[path.back()].prev);
        }

        for(auto it = path.rbegin(); it != path.rend(); ++it) {
            out << *it << "\n";
        }
    }
}
