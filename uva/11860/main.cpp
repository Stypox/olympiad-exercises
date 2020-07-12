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

bool lowercase(char c) {
	return (c >= 'a' && c <= 'z') || c=='E' || c=='N' || c=='D';
}

int32_t main() {
	int T;
	in >> T;

	char c=' ';
	for(int t = 0; t != T; ++t) {
		map<string, int> m;
		int i=0;
		vector<int> sentence;
		while(1){
			string word;
			while(!lowercase(c)) c=in.get();
			while(lowercase(c)) {
				word+=c;
				c=in.get();
			}

			if (word=="END") {
				break;
			} else {
				if (m.count(word) == 0) {
					m[word]=i;
					++i;
				}
				sentence.push_back(m[word]);
			}
		}

		int p=0,q=0;
		int words=0;
		vector<int> used(i, 0);
		while(1){
			++used[sentence[q]];
			if (used[sentence[q]] == 1) {
				++words;
			}

			if (words==i) break;
			++q;
		}
		deb("Before", p, q);

		int bestp=p,bestq=q;
		while(1) {
			while(used[sentence[p]] > 1) {
				--used[sentence[p]];
				++p;
			}

			if ((q-p) < (bestq-bestp)) {
				bestq = q;
				bestp = p;
			}

			++q;
			if (q >= sentence.size()) break;
			++used[sentence[q]];
		}

		deb("Done", bestp, bestq);
		out<<"Document "<<t+1<<": "<<bestp+1<<" "<<bestq+1<<"\n";
	}
}
