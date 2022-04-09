struct Node{
	int time=-1, minNeighbourTime=-1, parent=-1;
	vector<int> edges;
};

int32_t main() {
	while(1){
		int N;
		in>>N;
		if (!in) break;
		if(N==0) {
			out<<"0 critical links\n\n";
			continue;
		}

		vector<Node> nodes(N);
		for(int n = 0; n != N; ++n) {
			int a;
			in>>a;
			in.ignore(2);

			int M;
			in>>M;
			in.ignore();

			for(int m = 0; m != M; ++m) {
				int b;
				in>>b;
				nodes[a].edges.emplace_back(b);
				nodes[b].edges.emplace_back(a);
			}
		}

		int time=0;
		vector<pair<int,int>> bridges;
		function<void(int)> dfs = [&](int i){
			nodes[i].time = (nodes[i].minNeighbourTime = ++time);
			for(auto&& to : nodes[i].edges) {
				if (nodes[to].time==-1){
					nodes[to].parent = i;
					dfs(to);

					if (nodes[to].minNeighbourTime > nodes[i].time) {
						deb(to,i);
						bridges.emplace_back(min(i,to), max(i,to));
					}
					nodes[i].minNeighbourTime = min(nodes[i].minNeighbourTime, nodes[to].minNeighbourTime);
				} else if (to != nodes[i].parent) {
					nodes[i].minNeighbourTime = min(nodes[i].minNeighbourTime, nodes[to].time);
				}
			}
		};

		for(int n = 0; n != N; ++n) {
			if (nodes[n].time==-1){
				dfs(n);
			}
		}

		sort(bridges.begin(), bridges.end());
		out<<bridges.size()<<" critical links\n";
		for(auto&& bridge : bridges) {
			out<<bridge.first<<" - "<<bridge.second<<"\n";
		}
		out<<"\n";
		out.flush();
	}
}