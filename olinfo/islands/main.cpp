#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int R,C;
	in>>R>>C;

	vector<vector<bool>> land(R+2, vector<bool>(C+2, true));
	for(int r=0;r<R;++r){
		for(int c=0;c<C;++c){
			int i;
			in>>i;
			land[r+1][c+1] = (i != 0);
		}
	}

	R+=2;
	C+=2;
	function<void(int,int)> bucket_fill = [&](int r, int c) {
		if (r<0 || r>=R || c<0 || c>=C || !land[r][c]) return;
		land[r][c]=false;
		bucket_fill(r+1,c);
		bucket_fill(r-1,c);
		bucket_fill(r,c+1);
		bucket_fill(r,c-1);
	};

	int res=-1;
	for(int r=0;r<R;++r){
		for(int c=0;c<C;++c){
			if (land[r][c]) {
				bucket_fill(r,c);
				++res;
			}
		}
	}
	out<<res<<endl;
}
