#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define int int64_t
ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Street {
	int to,km;
};

struct Mem {
	int val=-1;
	vector<int> vec;
};

struct Node {
	Mem put;
	Mem empty;

	Street parent;
	vector<Street> children;
};

int32_t main() {
	int N;
	in>>N;

	/*vector<Node> nodes(N);
	for(int n=0;n<N-1;++n){
		int A,B,D;
		in>>A>>B>>D;
		--A;--B;

		if(A>B) swap(A,B);
		nodes[A].children.push_back({B,D});
		nodes[B].parent={A,D};
	}*/

	out<<N<<"\n";
	for(int n=1;n<=N;++n){
		out<<n<<" ";
	}
}