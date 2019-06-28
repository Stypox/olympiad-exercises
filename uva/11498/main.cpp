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
	while(1){
		si n,x0,y0;
		in>>n;
		if(n==0) return 0;
		in>>x0>>y0;

		for(int i = 0; i != n; ++i) {
			si x,y;
			in>>x>>y;
			if(x==x0||y==y0) out<<"divisa";
			else if(x>x0){
				if(y>y0) out<<"NE";
				else out<<"SE";
			}
			else{
				if(y>y0) out<<"NO";
				else out<<"SO";
			}
			out<<"\n";
		}
	}
}
