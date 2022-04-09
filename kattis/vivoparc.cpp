#include <bits/stdc++.h>
using namespace std;

struct Node{
	int animal = 0;
	set<int> sees;
};

int main(){
	int N;
	cin>>N;

	vector<Node> nodes(N);
	while(1) {
		int a, b;
		char t;
		cin>>a>>t>>b;
		a--; b--;
		if(cin.eof()) break;

		nodes[a].sees.insert(b);
		nodes[b].sees.insert(a);
	}

	function<void(int)> rec = [&](int i) {
		if (i == N) {
			for(int n=0;n<N;++n){
				cout<<n+1<<" "<<nodes[n].animal<<"\n";
			}
			exit(0);
		}

		bool used[5] {false, false, false, false, false};
		for (int j : nodes[i].sees) {
			if (j >= i) break;
			used[nodes[j].animal] = true;
		}

		for (int a = 1; a <= 4; ++a) {
			if (!used[a]) {
				nodes[i].animal = a;
				rec(i+1);
			}
		}
	};

	rec(0);
}