#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	string s;
	getline(cin, s);

	int N;
	cin>>N;
	cin.ignore();

	vector<vector<string>> exprs(N);
	for(int n=0;n<N;++n){
		getline(cin, s);
		exprs[n].push_back("");
		for (int i=0;i<s.size();++i){
			if (s[i]==',') {
				++i;
				exprs[n].push_back("");
				continue;
			}
			exprs[n].back().push_back(s[i]);
		}
	}

	int minsofar=numeric_limits<int>::max();
	vector<vector<string>> minsofarExprs;
	for (int n=0;n<N;++n){
		int maxChanges=0;
		for (int m=0;m<N;++m){
			int modif=0;
			for (int i=0;i<exprs[n].size();++i){
				if(exprs[n][i] != exprs[m][i])
					++modif;
			}
			maxChanges = max(maxChanges, modif);
		}

		if (maxChanges == minsofar) {
			minsofarExprs.push_back(exprs[n]);
		} else if (maxChanges < minsofar) {
			minsofar = maxChanges;
			minsofarExprs.clear();
			minsofarExprs.push_back(exprs[n]);
		}
	}

	for (auto&& v : minsofarExprs) {
		int first=true;
		for(auto&& s:v){
			if(!first){
				cout<<", ";
			}
			first=false;
			cout<<s;
		}
		cout<<"\n";
	}
}
