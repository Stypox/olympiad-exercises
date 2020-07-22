#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

struct Site{
	vector<int> c1, c2;

	int cost(int takenC1) {
		if (takenC1 == 0) {
			return c2.back();
		} else if (takenC1 == c1.size()) {
			return c1.back();
		} else {
			return c1[takenC1-1] + c2[c1.size() - takenC1 - 1];
		}
	}
};

int32_t main() {
	while(1){
		int T1,T2;
		in>>T1>>T2;
		if (T1==0&&T2==0) break;

		int N;
		in>>N;

		vector<Site> sites(N);
		for(int n = 0; n != N; ++n) {
			int M;
			in>>M;

			sites[n].c1.resize(M);
			sites[n].c2.resize(M);
			for(int m = 0; m != M; ++m) {
				in>>sites[n].c1[m];
			}
			for(int m = 0; m != M; ++m) {
				in>>sites[n].c2[m];
			}
		}

		vector<vector<vector<pair<int,int>>>> mem(sites.size(), vector<vector<pair<int,int>>>(T1+1, vector<pair<int,int>>(T2+1, {numeric_limits<int>::max(),-1})));
		function<int(int,int,int)> rec = [&](int i, int t1, int t2) -> int {
			if (t1 < 0 || t2 < 0) {
				return numeric_limits<int>::max() / 2;
			} else if (i>=sites.size()) {
				return 0;
			} else if (mem[i][t1][t2].second == -1) {
				for(int takenC1 = 0; takenC1 <= sites[i].c1.size(); ++takenC1) {
					int cost = sites[i].cost(takenC1) + rec(i+1, t1-takenC1, t2+takenC1-sites[i].c1.size());
					if (cost < mem[i][t1][t2].first) {
						mem[i][t1][t2].first = cost;
						mem[i][t1][t2].second = takenC1;
					}
				}
			}
			return mem[i][t1][t2].first;
		};

		out<<rec(0,T1,T2)<<"\n";
		int t1=T1,t2=T2;
		for(int i = 0; i != sites.size(); ++i) {
			if (i!=0) out<<" ";
			out<<mem[i][t1][t2].second;

			int newt1 = t1 - mem[i][t1][t2].second;
			t2 = t2 + mem[i][t1][t2].second - sites[i].c1.size();
			t1 = newt1;
			deb(i,t1,t2);
		}
		out<<"\n\n";
	}
}
