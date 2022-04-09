
signed main() {
	int C,D,Y;
	in>>C>>D>>Y;
	vector<int> M(D), P(D);
	for(int d=0;d<D;++d) in>>M[d];
	for(int d=0;d<D;++d) in>>P[d];

	vector<int> knapsack(D+1);
	knapsack[1] = C + M[0] - P[0];
	for(int d=1;d<D;++d){
		knapsack[d+1] = knapsack[d] + M[d] + P[d-1] - P[d];
	}
	deb(knapsack);

	Y++;
	vector<int> mem(Y, 0);
	for(int y=Y-2; y>=0; y--) {
		mem[y]=numeric_limits<int>::max();
		for(int d=1;d<=min(D, Y-y);++d){
			mem[y]=min(mem[y], knapsack[d] + mem[y+d]);
		}
	}

	out<<mem[0]<<"\n";
}