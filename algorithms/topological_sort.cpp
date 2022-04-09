struct Node {
	int consEntering=0;
	vector<int> cons;
};

int32_t main() {
	while(1){
		int N,M;
		in>>N>>M;
		if (N==0) break;

		vector<Node> nodes(N);
		for(int m = 0; m != M; ++m) {
			int a,b;
			in>>a>>b;
			--a;--b;
			// a va eseguito prima di b

			nodes[b].cons.push_back(a);
			nodes[a].consEntering++;
		}

		queue<int> q;
		for(int n = 0; n != N; ++n) {
			if (nodes[n].consEntering == 0) {
				q.push(n);
			}
		}

		vector<int> res;
		while(!q.empty()) {
			int n=q.front();
			q.pop();

			res.push_back(n);
			for (int con:nodes[n].cons){
				--nodes[con].consEntering;
				if(nodes[con].consEntering == 0) {
					q.push(con);
				}
			}
		}

		for(auto it = res.rbegin(); it != res.rend(); ++it) {
			if (it!=res.rbegin()) out<<" ";
			out<<(*it)+1;
		}
		out<<"\n";
	}
}