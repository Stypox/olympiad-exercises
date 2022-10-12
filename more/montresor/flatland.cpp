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

// poss. coppie: ss sd ds dd
// ss = 0
// ds = 0
// dd = 0
// sd ss = 0
// sd ds = 0
// ds sd = 0
// dd sd = 0
// sd sd = sd

template<typename Iter>
void isLeftRemovable(int N, string& S, Iter v) {
	bool dd_or_ds = false;
	bool doable = true;
	for(int n = 0; n < N-1; n += 2) {
		string piece = S.substr(n,2);
		if (piece == "ss") {
			// everything on the left is surely removable
			doable = true;
		} else if (piece == "sd") {
			// multiple of these simplify to one, need to be removed either from left or right
			doable = dd_or_ds;
		} else if (piece == "ds") {
			// can remove everything on left or on right, but not at the same time
			dd_or_ds = doable;
			doable = true;
		} else if (piece == "dd") {
			// everything on the right is surely removable, but keep state on left
			dd_or_ds = doable;
		}
		// the first item's left is always removable (there is nothing on the left!)
		v[n/2 + 1] = v[n/2 + 1] && doable;
	}
}

signed main() {
	int N;
	string S;
	in>>N>>S;

	assert(N%2 == 1);
	if (N != 1) {
		// the first and the last piece should never be taken
		S[0] = 's';
		S.end()[-1] = 'd';
	}

	// will be true only at indices n such that n*2 can remain alone
	vector<bool> v(N/2 + 1, true);
	isLeftRemovable(N, S, v.begin());

	// invert the string in order to reuse same function
	reverse(S.begin(), S.end());
	for (char& s : S) s = (s == 's' ? 'd' : 's');
	isLeftRemovable(N, S, v.rbegin());

	// find solution
	vector<int> res;
	for(int n = 0; n < N/2+1; ++n) {
		if (v[n]) {
			res.push_back(n*2);
		}
	}

	// print solution
	out<<res.size()<<"\n";
	for(size_t i=0;i<res.size();++i){
		if(i!=0){
			out<<" ";
		}
		out<<res[i];
	}
	out<<"\n";
}
