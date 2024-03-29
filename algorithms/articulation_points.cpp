struct Node{
	int time=-1, lowTime=-1;
	int parent=-1;
	bool articulation=false;
	vector<int> conn;
};

int32_t main() {
	while(1){
		int N;
		in>>N;
		if(N==0)break;

		vector<Node> nodes(N);
		while(1){
			int n;
			in>>n;
			if(n==0)break;
			--n;

			while(1){
				int b;
				in>>b;
				--b;

				nodes[n].conn.push_back(b);
				nodes[b].conn.push_back(n);
				if (in.get() == '\n') break;
			}
		}

		int time=1, rootChildren=0;
		function<void(int)> dfs = [&](int i) -> void {
			nodes[i].time = time;
			nodes[i].lowTime = time;
			++time;
			for(auto&& con : nodes[i].conn) {
				if (nodes[con].time == -1) {
					nodes[con].parent=i;
					if(i==0) ++rootChildren; // 0 is the root vertex of the dfs

					dfs(con);

					if (nodes[con].lowTime >= nodes[i].time) {
						// the child cannot be reached from other places
						nodes[i].articulation=true;

						if (nodes[con].lowTime > nodes[i].time) {
							// the edge i--con is a bridge
						}
					}

					nodes[i].lowTime = min(nodes[i].lowTime, nodes[con].lowTime);
				} else if (con != nodes[i].parent) {
					nodes[i].lowTime = min(nodes[i].lowTime, nodes[con].time);
				}
			}
		};

		dfs(0);
		// 0 is the root vertex of the dfs
		nodes[0].articulation = (rootChildren > 1);

		out<<count_if(nodes.begin(), nodes.end(), [](const Node& node) { return node.articulation; })<<"\n";
	}
}