#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define in cin
#define out cout

struct Node {
    vector<int> to;
    vector<int> from;
    int c;
    bool seen=false;
	int scc=-1;
};

struct SccNode{
	vector<int> to;
	int from=0;
	int c=0;
    bool used=false;
    int res=-2;
};

signed main() {
    int N,M;
    in>>N>>M;

	vector<Node> nodes(N);
    for(int n=0;n<N;++n){
        in>>nodes[n].c;
    }
	for(int m=0;m<M;++m){
		int a,b;
		in>>a>>b;
		nodes[a].to.push_back(b);
		nodes[b].from.push_back(a);
	}

	vector<int> s;
	function<void(int)> dfs = [&](int i) {
		if (nodes[i].seen) return;
		nodes[i].seen = true;

		for(auto&& e:nodes[i].to) {
			dfs(e);
		}
		s.push_back(i);
	};

	for(int n=0;n<N;++n){
		dfs(n);
	}

	int currScc = 0;
	vector<SccNode> sccNodes;
	function<void(int)> dfsRev = [&](int i) {
		if (nodes[i].scc != -1) {
			if (nodes[i].scc != currScc) {
				sccNodes[nodes[i].scc].to.push_back(currScc);
			}
			return;
		}
		nodes[i].scc = currScc;
        sccNodes.back().c += nodes[i].c;

		for(auto&& e:nodes[i].from) {
			dfsRev(e);
		}
	};

	for(auto it = s.rbegin(); it != s.rend(); ++it) {
		if (nodes[*it].scc == -1) {
			sccNodes.emplace_back();
			dfsRev(*it);
			currScc++;
		}
	}
    int start=nodes[0].scc, end=nodes[N-1].scc;
    deb(sccNodes.size(), start, end);
    for(int i=0;i<nodes.size();++i){
        deb("node", i, nodes[i].scc);
    }
    nodes.resize(0);


    function<int(int)> dp = [&](int i) -> int {
        if (i == end) return sccNodes[end].c;
        if (sccNodes[i].res != -2) return sccNodes[i].res;
        int best=-1;
        for(auto e:sccNodes[i].to) {
            best=max(best, dp(e));
        }
        if (best == -1) {
            sccNodes[i].res = -1;
            return -1;
        } else {
            best += sccNodes[i].c;
            sccNodes[i].res = best;
            return best;
        }
    };

    out<<dp(start)<<"\n";
    for(int i=0;i<sccNodes.size();++i){
        deb("scc", i, sccNodes[i].c, sccNodes[i].to, sccNodes[i].res);
    }
}
