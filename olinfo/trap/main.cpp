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

int readCompressedString() {
	string s;
	in>>s;
	assert(s.length() <= 10);
	assert(find(s.begin(), s.end(), ' ') == s.end());
	int res=0;
	for(auto c:s){
		res<<=5LL;
		res+=(c-'a'+1);
		assert((c-'a'+1) < (1<<5));
	}
	return res;
}

signed main() {
	int N,L,M;
	in>>N>>L>>M;

	vector<int> favWords;
	map<int, int> fav;
	for(int m=0;m<M;++m){
		favWords.push_back(readCompressedString());
		fav[favWords.back()] = 0;
	}

	for(int n=1;n<N;++n){
		int M1;
		in>>M1;
		set<int> words;
		for(int m=0;m<M1;++m){
			words.insert(readCompressedString());
		}
		for(auto w:words){
			if(fav.count(w)) {
				fav[w]++;
			}
		}
	}

	for(int m=0;m<M;++m){
		out<<fav[favWords[m]]<<" ";
	}
}
