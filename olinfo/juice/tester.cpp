#include <bits/stdc++.h>
using namespace std;

int main() {
	auto seed = 1620324835358879013LL;//std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	ofstream{"seed.txt"} << seed;

	int N=2+rand()%18;
	int M=1+rand()%(N-1);
	cout<<N<<" "<<M<<" "<<50<<"\n0";

	for(int n=1;n<N;++n) {
		cout<<" "<<(rand()%n);
	}
	cout<<"\n";

	vector<int> V;
	while(V.size() != M){
		int v=rand()%N;
		if(find(V.begin(), V.end(), v) == V.end()) {
			V.push_back(v);
		}
	}

	for(int m=0;m<M;++m){
		cout<<V[m]<<" "<<(rand() % 50)<<" "<<1<<"\n";
	}
}