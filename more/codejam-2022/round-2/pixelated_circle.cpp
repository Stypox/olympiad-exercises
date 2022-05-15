#include<bits/stdc++.h>
using namespace std;

signed main() {
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int R;
		cin>>R;

		vector<vector<bool>> m(2*R+3, vector<bool>(2*R+3, false));
		for(int x=0;x<=R;++x){
			for(int y=0;y<=R;++y){
				if (round(sqrt(x*x + y*y)) <= R) {
					m[ x+R+1][ y+R+1] = true;
					m[-x+R+1][ y+R+1] = true;
					m[ x+R+1][-y+R+1] = true;
					m[-x+R+1][-y+R+1] = true;
				}
			}
		}

		for(int r=0;r<=R;++r){
			for(int x=-r;x<=r;++x) {
				int y=round(sqrt(r*r - x*x));
				m[ x+R+1][ y+R+1] = false;
				m[-x+R+1][ y+R+1] = false;
				m[ x+R+1][-y+R+1] = false;
				m[-x+R+1][-y+R+1] = false;
				m[ y+R+1][ x+R+1] = false;
				m[-y+R+1][ x+R+1] = false;
				m[ y+R+1][-x+R+1] = false;
				m[-y+R+1][-x+R+1] = false;
			}
		}

		int c=0;
		for(auto&& v:m){
			for(bool b:v){
				//cout<<(b?'#':' ');
				c+=b;
			}
			//cout<<"|"<<endl;
		}

		cout<<"Case #"<<t+1<<": "<<c<<endl;
	}
}