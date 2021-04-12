#include <bits/stdc++.h>
using namespace std;

#define int long long
ifstream in{"input.txt"};
ofstream out{"output.txt"};


signed main() {
	int T;
	in>>T;
	for (int t=0;t<T;++t){
		int N,K;
		in>>N>>K;

		vector<int> S(N);
		vector<int> indexes(N);
		vector<int> people(N);
		vector<bool> seen(N, false);
		for(int n=0;n<N;++n){
			people[n]=n;
			in>>S[n];
		}

		function<void(int, int, vector<int>&)> rec = [&](int i, int ci, vector<int>& v) -> void {
			if (!seen[i]) {
				indexes[i] = ci;
				seen[i] = true;
				v.push_back(i);
				rec(S[i], ci, v);
			}
		};

		vector<vector<int>> cycles;
		for (int n=0;n<N;++n){
			if(!seen[n]) {
				vector<int> v{};
				rec(n,cycles.size(),v);
				cycles.push_back(v);
			}
		}

		fill(seen.begin(), seen.end(), false);
		for(int n=0;n<N;++n) {
			if (!seen[n]) {
				vector<int>& cycle = cycles[indexes[n]];
				vector<int> vals(cycle.size());
				for (int a=0;a<cycle.size();++a) {
					seen[cycle[a]] = true;
					vals[a]=people[cycle[a]];
				}

				int K1 = (cycle.size() - K % cycle.size()) % cycle.size();
				vector<int> vals2(vals.begin() + K1, vals.end());
				vals2.insert(vals2.end(), vals.begin(), vals.begin() + K1);
				for (int a=0;a<cycle.size();++a) {
					people[cycle[a]] = vals2[a];
				}
			}
		}

		out<<"Case #"<<t+1<<":";
		for(int n=0;n<N;++n){
			out<<" "<<people[n];
		}
		out<<"\n";
	}
}