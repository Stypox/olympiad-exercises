#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

void tryAll(int g, set<int>& res) {
	for(int i=1;i<=sqrt(g)+5;++i){
		if (g%i==0) {
			res.insert(i);
			res.insert(g/i);
		}
	}
}

int main() {
	int T;
	cin>>T;
	while(T--){
		int W,L;
		cin>>W>>L;
		set<int> res;
		tryAll(gcd(W-1, L-1), res);
		tryAll(gcd(W-2, L),   res);
		tryAll(gcd(W,   L-2), res);
		tryAll(gcd(W,   2),   res);
		tryAll(gcd(2,   L),   res);
		cout<<res.size();
		for(auto i=res.begin();i!=res.end();++i){
			cout<<" "<<*i;
		}
		cout<<"\n";
	}
}