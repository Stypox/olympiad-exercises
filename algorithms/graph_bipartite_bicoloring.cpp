struct Node {
	int color=-1;
	vector<int> conn;
};

int32_t main() {
	while(1){
		int N,L;
		in>>N;
		if(N==0) break;
		in>>L;

		vector<Node> nodes(N);
		for(int l = 0; l != L; ++l) {
			int a,b;
			in>>a>>b;
			nodes[a].conn.push_back(b);
			nodes[b].conn.push_back(a);
		}

		queue<pair<int,int>> q;
		q.push({0,0});
		bool doable=true;
		while (!q.empty()) {
			auto [i,c] = q.front();
			deb(i,c);
			q.pop();

			if (nodes[i].color == -1) {
				nodes[i].color=c;
				for(auto&& con : nodes[i].conn) {
					q.push({con, (c+1)%2});
				}
			} else {
				if (nodes[i].color!=c) {
					doable=false;
					break;
				}
			}
		}

		deb();
		out<<(doable?"BICOLORABLE.\n":"NOT BICOLORABLE.\n");
	}
}
