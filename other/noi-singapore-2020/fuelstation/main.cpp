#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define int int64_t
ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Station {
	int X,A,B;
};

int32_t main() {
	int N,D;
	in>>N>>D;

	vector<Station> ss(N);
	ss.push_back({0,0,0});
	for(auto&& stat:ss){
		in>>stat.X>>stat.A>>stat.B;
	}
	sort(ss.begin(), ss.end(), [](const Station& a, const Station& b) { return a.X<b.X; });
	ss.push_back({D,0,0});

	function<int(int,int,int)> calc = [&](int F, int f, int i) -> int {
		if (f<0) return -f;
		if (i==N) return 0;

		int f1 = f-ss[i+1].X+ss[i].X;
		if (F <= ss[i].B) {
			return calc(F, f1+ss[i].A,i+1);
		} else {
			return calc(F, f1,i+1);
		}
	};


	for(int i=0;i<=D;){
		int val = calc(i,i-ss[0].X,0);
		if(val==0) {
			out<<i<<"\n";
			break;
		}
		i+=val;
	}
	return 0;

	int needed=0;
	int maxstart=0;
	for(int i=N+1;i>0;--i) {
		int sub = needed - ss[i].A;
		if(sub <= 0) {
			needed = 0;
		} else {
			if(sub<=ss[i].B){
				maxstart=max(maxstart,sub);
				needed=sub;
			} else {
				// needed is unchanged
			}
		}
		needed+=(ss[i].X-ss[i-1].X);
	}

	out<<max(needed,maxstart)<<"\n";
}