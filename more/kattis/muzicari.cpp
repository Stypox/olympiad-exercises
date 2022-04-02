#include <bits/stdc++.h>
using namespace std;

int main(){
	int T,N;
	cin>>T>>N;

	vector<int> P(N),S{0};
	int prevSum = 0;
	for(int n=0;n<N;++n){
		cin>>P[n];
		S.push_back(prevSum += P[n]);
	}

	vector<int> where(N);
	vector<vector<int>> mem(T+1, vector<int>(N, -1));
	function<bool(int,int)> rec = [&](int s1, int n) {
		if (n != 0 && (s1 > T || (S[n]-s1) > T)) return false;
		if (n == N) return true;

		if (mem[s1][n] == -1) {
			where[n] = s1;
			if (rec(s1 + P[n], n+1)) {
				mem[s1][n] = 1;
			} else {
				where[n] = S[n]-s1;
				mem[s1][n] = rec(s1, n+1);
			}
		}

		return (bool)mem[s1][n];
	};

	assert(rec(0,0));
	for(int n=0;n<N;++n){
		if (n!=0) {
			cout<<" ";
		}
		cout<<where[n];
	}
	cout<<"\n";
}