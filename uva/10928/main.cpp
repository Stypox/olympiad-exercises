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
		int P;
		in >> P;
		in.ignore();

		int smallestDegree = numeric_limits<int>::max();
		vector<int> smallestDegreeVertices;
		for (int p = 0; p < P; p++) {
			string line;
			getline(in, line);
			int degree = count(line.begin(), line.end(), ' ');

			if (degree == smallestDegree) {
				smallestDegreeVertices.push_back(p+1);
			} else if (degree < smallestDegree) {
				smallestDegree = degree;
				smallestDegreeVertices = vector<int>{p+1};
			}
		}
		
		out<<smallestDegreeVertices[0];
		for(int i=1;i<smallestDegreeVertices.size();++i) {
			out<<' '<<smallestDegreeVertices[i];
		}
		out<<'\n';
	}
}
