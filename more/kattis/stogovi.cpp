#include <bits/stdc++.h>
using namespace std;
constexpr int BINARY_LIFTING_SIZE = 19;

struct Node{
	int value, depth;
	array<Node*, BINARY_LIFTING_SIZE> sparseParents;

	Node() : value{0}, depth{0} {
		fill(sparseParents.begin(), sparseParents.end(), this);
	}
	Node(int val, Node* par) : value{val}, depth{par->depth+1} {
		sparseParents[0]=par;
		for(int i=1;i<BINARY_LIFTING_SIZE;++i){
			sparseParents[i]=sparseParents[i-1]->sparseParents[i-1];
		}
	}
};

int main(){
	int N;
	cin>>N;

	Node root;
	vector<Node*> stackPointers{&root};
	vector<unique_ptr<Node>> nodeStorage;
	for(int n=1;n<=N;++n){
		string s;
		int v;
		cin>>s>>v;

		if(s=="a"){
			nodeStorage.push_back(make_unique<Node>(n, stackPointers[v]));
			stackPointers.push_back(nodeStorage.back().get());

		} else if(s=="b"){
			cout<<stackPointers[v]->value<<"\n";
			stackPointers.push_back(stackPointers[v]->sparseParents[0]);

		} else{
			assert(s=="c");
			int w;
			cin>>w;

			Node* a=stackPointers[v];
			Node* b=stackPointers[w];
			if(a->depth>b->depth) swap(a,b);

			int depthDiff = b->depth - a->depth;
			for(int i=0;i<BINARY_LIFTING_SIZE;++i){
				if(depthDiff&(1<<i)) b=b->sparseParents[i];
			}
			assert(a->depth==b->depth);

			for(int i=BINARY_LIFTING_SIZE-1;i>=0;--i){
				if(a->sparseParents[i] != b->sparseParents[i]){
					a = a->sparseParents[i];
					b = b->sparseParents[i];
				}
			}
			assert(a->sparseParents[0]==b->sparseParents[0]);
			Node* lca = (a==b ? a : a->sparseParents[0]);

			cout<<lca->depth<<"\n";
			stackPointers.push_back(stackPointers[v]);
		}
	}
}
