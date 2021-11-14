#include <bits/stdc++.h>
using namespace std;

struct Node{

};

int main(){
	int N;
	cin>>N;

	int res=0;
	for (int n=0;n<N;++n){
		int l;
		cin>>l;
		res+=(l<0);
	}

	cout<<res<<"\n";
}