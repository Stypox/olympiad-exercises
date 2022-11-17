#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
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

struct Node{
	vector<int> to,from;
	bool seen=false;
	int scc=-1;
};

struct SccNode{
	vector<int> to;
	int from=0;
	int ways=0;
};

signed main() {
	int N,M,S,D;
	in>>N>>M>>S>>D;

	vector<Node> nodes(N);
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

	S=nodes[S].scc;
	D=nodes[D].scc;
	deb(currScc, S, D);

	function<void(int)> dfsScc = [&](int i){
		sccNodes[i].from++;
		if(sccNodes[i].from > 1) return;

		for(auto&& e:sccNodes[i].to){
			dfsScc(e);
		}
	};
	dfsScc(S);
	for(int i=0;i<currScc;++i){
		deb(i, sccNodes[i].to, sccNodes[i].from);
	}

	queue<pair<int,int>> q;
	q.push({S,1});
	while(!q.empty()) {
		auto[i,ways]=q.front();
		q.pop();

		sccNodes[i].ways += ways;
		sccNodes[i].from--;

		if (sccNodes[i].from == 0) {
			for(auto&& e:sccNodes[i].to){
				q.push({e,sccNodes[i].ways});
			}
		}
	}

	for(int i=0;i<currScc;++i){
		deb(i, sccNodes[i].to, sccNodes[i].ways);
	}
	assert(sccNodes[D].ways != 0);
	out<<sccNodes[D].ways<<"\n";
}
