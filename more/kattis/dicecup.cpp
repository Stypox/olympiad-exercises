#include <bits/stdc++.h>
using namespace std;

int main(){
	int N,M;
	cin>>N>>M;

	vector<int> sums(N+M+1);
	for(int n=1;n<=N;++n){
		for(int m=1;m<=M;++m){
			++sums[n+m];
		}
	}

	int maxlikeliness = *max_element(sums.begin(), sums.end());
	for(int s=0;s<sums.size();++s){
		if(sums[s] == maxlikeliness){
			cout<<s<<"\n";
		}
	}
}