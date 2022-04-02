#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MOD = 1'000'000'007LL;

signed main(){
	int N;
	string W;
	cin>>N>>W;

	vector<string> strings(N);
	vector<int> multipliers(N);
	for(int n=0;n<N;++n){
		cin>>strings[n]>>multipliers[n];
	}

	vector<int> mem(W.length(),-1);
	function<int(int)> ways = [&](int w) -> int {
		if (w>=W.length()) return 1;
		if (mem[w] == -1) {
			mem[w] = 0;
			for(int n=0;n<N;++n){
				if(strings[n].length() <= W.length()-w
						&& memcmp(strings[n].c_str(), W.c_str() + w, strings[n].length()) == 0) {
					mem[w] += multipliers[n] * ways(w+strings[n].length()) % MOD;
					mem[w] %= MOD;
				}
			}
		}
		return mem[w];
	};

	cout<<ways(0)<<"\n";
}