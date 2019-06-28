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
template<class... Ts> constexpr void deb(const Ts&...) {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#endif

int main() {
	while(1) {
		si N,B,H,W;
		in>>N>>B>>H>>W;
		if(!in) break;

		bool found=false;
		si minp=numeric_limits<si>::max();
		for(int h = 0; h != H; ++h) {
			si p;
			in>>p;

			for(int w = 0; w != W; ++w) {
				si a;
				in>>a;
				if(a>=N && p<minp) {
					found=true;
					minp = p;
				}
			}
		}

		if(found && (minp*N)<=B) {
			out<<minp*N;
		} else {
			out<<"stay home";
		}
		out<<"\n";
	}
}
