#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define int int64_t
ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Road {
	int to=-1, w;
};

bool operator<(const Road& a, const Road& b) {
	return a.w>b.w;
}

struct SpConn {
	int from=-1, to=-1, w;
};

struct Node {
	vector<Road> roads;
	int seen=-1;
	SpConn nearestNode1;
	SpConn nearestNode2;
	bool special;
};


int32_t main() {
	int N,M,K;
	in>>N>>M>>K;

	vector<Node> nodes(N);
	for(int m=0;m<M;++m){
		int U,V,W;
		in>>U>>V>>W;
		U--;V--;

		nodes[U].roads.push_back({V,W});
		nodes[V].roads.push_back({U,W});
	}

	vector<int> specials(K);
	for(int k=0;k<K;++k){
		in>>specials[k];
		specials[k]--;
		nodes[specials[k]].special = true;
	}


	auto popul = [&](int k) {
		priority_queue<Road> pq;
		nodes[k].seen=k;
		for(auto&& road:nodes[k].roads) {
			pq.push(road);
		}

		while(!pq.empty()) {
			Road r=pq.top();
			pq.pop();

			nodes[r.to].seen=k;
			if (nodes[r.to].special) {
				if (nodes[k].nearestNode1.to==-1){
					nodes[k].nearestNode1 = {k,r.to,r.w};
					continue;
				} else {
					nodes[k].nearestNode2 = {k,r.to,r.w};
					return;
				}
			}

			for(auto&& road:nodes[r.to].roads) {
				if (nodes[road.to].seen != k) {
					pq.push({road.to, r.w+road.w});
				}
			}
		}
	};


	int
	for(int sp:specials){
		if (sp==0||sp==1) continue;
		popul(sp);
		if(nodes[sp].nearestNode1.to!=-1){
			segments.push_back(nodes[sp].nearestNode1);
		}
		if(nodes[sp].nearestNode2.to!=-1){
			segments.push_back(nodes[sp].nearestNode2);
		}
	}

	int minsum=numeric_limits<int>::max();
	for(auto s1:segments){
		for(auto s2:segments){
			if(s1.to==s2.to||s1.to==s2.from||s1.from==s2.to||s1.from==s2.from) {
				continue;
			} else {
				minsum = min(s1.w + s2.w, minsum);
			}
		}
	}

	out<<minsum<<"\n";
}