signed main() {
	int N,M;
	in>>N>>M;
	int S=0, T=N-1;

	vector<vector<int>> adj(N), capacity(N, vector<int>(N, 0));
	for(int m=0;m<M;++m) {
      int A,B,C;
      in>>A>>B>>C;
      A--; B--;
      adj[A].push_back(B);
      adj[B].push_back(A);
      capacity[A][B] += C;
	}

   vector<int> parent(N);
	auto bfsAugmentingPath = [&]() -> int {
	   fill(parent.begin(), parent.end(), -1);
	   parent[S] = -2; // prevent passing through S
	   queue<pair<int, int>> q;
	   q.push({S, numeric_limits<int>::max()});

	   while (!q.empty()) {
         auto [i, flow] = q.front();
         q.pop();

         for (int e : adj[i]) {
            if (capacity[i][e] > 0 && parent[e] == -1) {
               parent[e] = i;
               if (e == T) return min(flow, capacity[i][e]);
               q.push({e, min(flow, capacity[i][e])});
            }
         }
	   }
	   return 0;
	};

   int flow=0;
	while(1) {
      int partialFlow = bfsAugmentingPath();
      if (partialFlow == 0) break;
      flow += partialFlow;

      int last=T;
      while(last!=S){
         capacity[parent[last]][last] -= partialFlow;
         capacity[last][parent[last]] += partialFlow;
         last = parent[last];
      }
   }

   out<<flow<<"\n";
}