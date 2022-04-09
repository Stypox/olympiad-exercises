#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int a,b;
	cin>>a>>b;

	int res=0;
	if(a%2==0){
		res=1;
		for(int x=0;x<b;++x){
			res*=(a/2);
			res%=a;
		}
	}
	cout<<res<<"\n";
}