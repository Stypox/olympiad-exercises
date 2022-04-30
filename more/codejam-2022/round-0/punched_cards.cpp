#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;

	for(int t=0;t<T;++t) {
		int R, C;
		cin>>R>>C;

		cout<<"Case #"<<t+1<<":";

		cout<<"\n..+";
		for(int c=1;c<C;++c) cout<<"-+";

		cout<<"\n..|";
		for(int c=1;c<C;++c) cout<<".|";

		cout<<"\n+";
		for(int c=0;c<C;++c) cout<<"-+";

		for(int r=1;r<R;++r){
			cout<<"\n|";
			for(int c=0;c<C;++c) cout<<".|";
			cout<<"\n+";
			for(int c=0;c<C;++c) cout<<"-+";
		}
		cout<<"\n";
	}
}
