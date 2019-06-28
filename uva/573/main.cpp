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
	while(1){
		si H,D,F;
		flt U;
		in>>H>>U>>D>>F;
		if(H==0)break;

		flt f=F*U/100.0;

		si d=1;
		flt h=0;
		while(1){
			h+=U;
			if(h>H){
				out<<"success";
				break;
			}
			h-=D;
			if(h<0){
				out<<"failure";
				break;
			}

			U-=f;
			U=max(0.0L,U);
			++d;
		}
		out<<" on day "<<d<<"\n";
	}
}
