#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;

	while(T--){
		vector<vector<bool>> right(360, vector<bool>(21, false)),
			bottom(360, vector<bool>(21, false)),
			seen(360, vector<bool>(21, false));

		int N;
		cin>>N;
		for(int n=0;n<N;++n){
			string s;
			cin>>s;
			if (s[0] == 'C') {
				int r,t1,t2;
				cin>>r>>t1>>t2;
				r--;
				if (t2<t1) t2+=360;
				for(int t=t1; t<t2; ++t) {
					bottom[t % 360][r]=true;
				}
			} else {
				int r1,r2,t;
				cin>>r1>>r2>>t;
				t+=360-1;
				t%=360;
				for(int r=r1; r<r2; ++r) {
					right[t][r]=true;
				}
			}
		}

		#ifdef DEBUG
		for(int r=0;r<21;++r){
			cout<<"#";
			for(int t=0;t<360;++t){
				if(bottom[t][r] && right[t][r]) cout<<"/";
				else if(bottom[t][r]) cout<<"_";
				else if(right[t][r]) cout<<"|";
				else cout<<" ";
			}
			cout<<"#\n";
		}
		#endif

		function<bool(int,int)> doable = [&](int t, int r) {
			t += 360;
			t %= 360;
			if (r>20) return true;
			if (r<0) return false;
			if (seen[t][r]) return false;
			seen[t][r] = true;

			if (!bottom[t][r] && doable(t, r+1)) return true;
			if (!right[t][r] && doable(t+1, r)) return true;
			if (r>0 && !bottom[t][r-1] && doable(t, r-1)) return true;
			if (!right[(t+360-1)%360][r] && doable(t-1, r)) return true;
			return false;
		};

		cout << (doable(0,0) ? "YES" : "NO") << endl;
	}
}