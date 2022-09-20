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

	vector<vector<int>> cumsum(R+1, vector<int>(C+1, 0));
	for(int r=0;r<R;++r){
		for(int c=0;c<C;++c){
			int v;
			in>>v;
			cumsum[r+1][c+1] = cumsum[r+1][c] + cumsum[r][c+1] - cumsum[r][c] + v;
		}
	}

	auto sommaSottomatriceComplementare = [&](int r1, int r2, int c1, int c2) {
		return cumsum[r2+1][c2+1] - cumsum[r2+1][c1] - cumsum[r1][c2+1] + cumsum[r1][c1];
	};

	int res=0;
	for(int r1=0;r1<R;++r1){
		for(int r2=r1;r2<R;++r2){
			int s=0, c=0;
			while(c<C) {
				s += sommaSottomatriceComplementare(r1, r2, c, c);
				res=max(res,s);
				c++;
				if (s < 0) {
					s=0;
				}
			}
		}
	}

	out<<res<<"\n";
}
