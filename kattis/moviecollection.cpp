#include <bits/stdc++.h>
using namespace std;

int leastSignificantOneBit(int i){
	return i & (-i);
}

struct FenwickTree {
	vector<int> data;
	FenwickTree(int N) : data(N) {}
	void add(int pos, int value) {
		if (pos>=data.size()) return;
		data[pos] += value;
		add(pos + leastSignificantOneBit(pos), value);
	}
	int sumUpTo(int pos) {
		if (pos==0) return 0;
		return data[pos] + sumUpTo(pos - leastSignificantOneBit(pos));
	}
};

int main(){
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int M,R;
		cin>>M>>R;

		vector<int> lastMoveTimestamp(M);
		FenwickTree moveTimestamps(M+R+1);

		iota(lastMoveTimestamp.rbegin(), lastMoveTimestamp.rend(), 1);
		for(int m=0;m<M;++m){
			moveTimestamps.add(m+1, 1);
		}

		for(int r=0;r<R;++r){
			int a;
			cin>>a;
			a--;

			if(r!=0) cout<<" ";
			cout<<(M - 1 - moveTimestamps.sumUpTo(lastMoveTimestamp[a]-1));
			moveTimestamps.add(lastMoveTimestamp[a], -1);
			lastMoveTimestamp[a] = M+r+1;
			moveTimestamps.add(lastMoveTimestamp[a], 1);
		}
		cout<<"\n";
	}
}
