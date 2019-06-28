#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
#endif

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		array<si,3> a;
		in>>a[0]>>a[1]>>a[2];
		sort(a.begin(),a.end());
		out<<"Case "<<t+1<<": "<<a[1]<<"\n";
	}
}
