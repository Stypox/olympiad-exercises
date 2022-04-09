#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin>>N;

	vector<int> W(N);
	for(int n=0;n<N;++n){
		cin>>W[n];
	}

	vector<vector<int>> mem(N, vector<int>(2001, -1));
	function<int(int, int)> rec = [&](int n, int sumSoFar) -> int {
		if(sumSoFar>2000) return 2001;
		if(n==N) return sumSoFar;
		if(mem[n][sumSoFar] != -1) return mem[n][sumSoFar];

		int a = rec(n+1, sumSoFar + W[n]);
		int b = rec(n+1, sumSoFar);

		if (a > b) swap(a, b);
		int res = b;
		if (abs(1000-a) < abs(b-1000)) res = a;
		return mem[n][sumSoFar] = res;
	};

	cout<<rec(0,0)<<"\n";
}