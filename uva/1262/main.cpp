#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

int32_t main() {
	int T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		int K;
		in>>K;
		vector<string> col1(5), col2(5);

		for(int r=0;r<6;++r){
			in.ignore();
			for(int c=0;c<5;++c){
				char l;
				in>>l;
				col1[c].push_back(l);
			}
		}
		for(int r=0;r<6;++r){
			in.ignore();
			for(int c=0;c<5;++c){
				char l;
				in>>l;
				col2[c].push_back(l);
			}
		}

		vector<string> col(5); // in comune
		for(int c=0;c<5;++c){
			for(int r=0;r<6;++r){
				if(col2[c].find(col1[c][r]) != std::string::npos
						&& col[c].find(col1[c][r]) == std::string::npos){
					col[c].push_back(col1[c][r]);
				}
			}
			sort(col[c].begin(), col[c].end());
		}

		string result;
		int k=0;
		function<bool(int)> rec = [&](int c) {
			if (c==5){
				++k;
				return k==K;
			}

			for(char r:col[c]){
				if (rec(c+1)) {
					result.push_back(r);
					return true;
				}
			}
			return false;
		};

		if (rec(0)) {
			out<<string(result.rbegin(), result.rend())<<"\n";
		} else {
			out<<"NO\n";
		}
	}
}
