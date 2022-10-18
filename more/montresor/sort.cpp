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
	int N;
	in>>N;

	vector<int> values(N);
	for(int n=0; n<N; ++n){
		in>>values[n];
	}

	// iterative merge sort
	vector<int> temp(N);
	for(int i = 2; i < 2*N; i *= 2) {
		for(int s = 0; s < N; s += i) {
			int h = min(s + i/2, N);
			int e = min(s + i, N);

			int t = 0;
			int l = s, r = h;
			while (true) {
				if (l >= h) {
					if (r >= e) {
						break;
					}
					temp[t] = values[r];
					++r;
				} else if (r >= e || values[l] <= values[r]) {
					temp[t] = values[l];
					++l;
				} else {
					temp[t] = values[r];
					++r;
				}
				++t;
			}

			copy(temp.begin(), temp.begin() + t, values.begin() + s);
		}
	}

	for(int n=0; n<N; ++n) {
		if (n!=0) out << " ";
		out << values[n];
	}
	out << "\n";
}
