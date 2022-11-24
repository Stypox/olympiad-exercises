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
	vector<pair<int,int>> to;
	int dist=numeric_limits<int>::max();
	vector<int> toDijkstra;
	bool visited=false;
	int master=-1;
	int subordinated=0;
};

struct Data{
	int dist,i,par;
};

signed main() {
	int N,M,P;
	in>>N>>M>>P;

	vector<Node> nodes(N);
	for(int m=0;m<M;++m){
		int a,b,w;
		in>>a>>b>>w;
		nodes[a].to.push_back({b,w});
		nodes[b].to.push_back({a,w});
	}

	auto cmp = [](const Data& a, const Data& b) { return a.dist > b.dist; };
	priority_queue<Data, vector<Data>, decltype(cmp)> pq{cmp};
	pq.push({0,P,P});
	while(!pq.empty()) {
		Data data = pq.top();
		pq.pop();

		if (data.dist <= nodes[data.i].dist) {
			nodes[data.i].toDijkstra.clear();
			if (data.par != data.i) {
				nodes[data.par].toDijkstra.push_back(data.i);
			}

			if (data.dist < nodes[data.i].dist) {
				nodes[data.i].dist = data.dist;
				for(auto [e,w]:nodes[data.i].to){
					pq.push({data.dist+w,e,data.i});
				}
			}
		}
	}

	vector<int> toposorted;
	function<void(int)> toposort = [&](int i) {
		if (nodes[i].visited) {
			return;
		}
		nodes[i].visited = true;

		for(auto&& e:nodes[i].toDijkstra){
			toposort(e);
		}

		toposorted.push_back(i);
	};
	toposort(P);

	for(int n=0;n<N;++n){
		for(auto&&e:nodes[n].toDijkstra){
			deb(n,e);
		}
	}
	deb(toposorted);

	for(auto&& e:nodes[P].toDijkstra){
		nodes[e].master=e;
		nodes[e].subordinated=1;
	}
	for(auto it = toposorted.rbegin()+1; it != toposorted.rend(); ++it) {
		for(auto&& e:nodes[*it].toDijkstra){
			if (nodes[e].master == -1) {
				nodes[e].master = nodes[*it].master;
				nodes[nodes[*it].master].subordinated++;
			} else if (nodes[e].master != nodes[*it].master) {
				nodes[nodes[e].master].subordinated--;
				nodes[e].master=e;
				nodes[e].subordinated++;
			}
		}
	}

	nodes[P].subordinated=0;
	int iCityMax, subordinatedCityMax=-1;
	for(int n=0;n<N;++n){
		deb(nodes[n].subordinated, nodes[n].master);
		if(nodes[n].subordinated > subordinatedCityMax) {
			iCityMax=n;
			subordinatedCityMax=nodes[n].subordinated;
		}
		nodes[n].visited = false;
	}

	out<<subordinatedCityMax<<"\n";
	for(int n=0;n<N;++n){
		if(nodes[n].master==iCityMax){
			out<<n<<"\n";
		}
	}
}
