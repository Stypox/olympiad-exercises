#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

signed main(){
	int N;
	cin>>N;

	vector<bool> seen(26);
	vector<int> coeff(26);
	vector<bool> cantBeZero(26);
	for (int n=0;n<N;++n){
		string s;
		cin>>s;
		for(int i=0;i<s.size();++i){
			seen[s[i] - 'A'] = true;
			coeff[s.end()[-i-1] - 'A'] += pow10[i] * (n == N-1 ? -1 : 1);
		}
		cantBeZero[s[0] - 'A'] = true;
	}

	vector<int> coeff2;
	vector<bool> cantBeZero2;
	for (int i=0;i<26;++i){
		//cerr<<(char)('A'+i)<<" "<<coeff[i]<<" "<<cantBeZero[i]<<"\n";
		if (seen[i]){
			coeff2.push_back(coeff[i]);
			cantBeZero2.push_back(cantBeZero[i]);
		}
	}
	//cerr<<coeff2.size()<<"\n";

	int tot = 0;
	vector<bool> used(10);
	function<void(int,int)> rec = [&](int i, int s) {
		if (i == coeff2.size()) {
			tot += (int)(s==0);
			return;
		}

		for(int v=cantBeZero2[i];v<10;++v){
			if (used[v]) continue;
			used[v] = true;
			rec(i+1, s + coeff2[i]*v);
			used[v] = false;
		}
	};

	rec(0, 0);
	cout<<tot<<"\n";
}