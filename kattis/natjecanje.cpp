#include <bits/stdc++.h>
using namespace std;

int main(){
	int N,S,R;
	cin>>N>>S>>R;

	vector<bool> dam(N,false), res(N,false);
	for (int s=0;s<S;++s){
		int x;
		cin>>x;
		--x;
		dam[x]=true;
	}
	for (int s=0;s<R;++s){
		int x;
		cin>>x;
		--x;
		res[x]=true;
	}

	for (int n=0;n<N;++n){
		if (dam[n] && res[n]) {
			dam[n]=false;
			res[n]=false;
		}
	}

	function<int(int,bool,bool)> rec = [&](int i, bool prevCanGive, bool prevHasTaken) -> int {
		if (i==N) {
			return 0;
		} else if (dam[i]) {
			if (prevCanGive) {
				return rec(i+1, false, false);
			} else if (i<N-1 && res[i+1]) {
				return rec(i+1, false, true);
			} else {
				return 1 + rec(i+1, false, false);
			}
		} else {
			return rec(i+1, res[i] && (!prevHasTaken), false);
		}
	};

	cout<<rec(0, false, false)<<"\n";
}