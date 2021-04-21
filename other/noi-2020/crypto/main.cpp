#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define int int64_t
ifstream in{"input.txt"};
ofstream out{"output.txt"};

using it = vector<int>::iterator;
vector<int> remap(const it& begin, const it& end) {
	vector<int> sorted(begin,end);
	sort(sorted.begin(), sorted.end());

	int n=distance(begin,end);
	vector<int> res(n);
	for(int i=0;i<n;++i){
		res[i] = distance(sorted.begin(), find(sorted.begin(), sorted.end(), *(begin+i)));
	}
	return res;
}

int32_t main() {
	int N;
	in>>N;

	vector<int> P(N);
	for(auto&& e:P){
		in>>e;
	}

	vector<int> fact(N);
	fact[0]=1;
	for(int i=1;i<N;++i){
		fact[i] = (fact[i-1]*i)%MOD;
	}


	int tot=1;
	set<int> vals;
	for(int n=N-1;n>=0;--n){
		int dist = distance(vals.begin(), vals.lower_bound(P[n]));
		vals.insert(P[n]);

		if (dist>0) {
			tot+=dist*fact[N-n-1];
		}
	}


	out<<tot<<"\n";
}