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
	si k=0;
	while(1){
		si N,P;
		in>>N>>P; in.ignore();
		if(N==0&&P==0)break;
		
		str tmp;
		for(int n = 0; n != N; ++n) getline(in,tmp);

		si maxR = -1;
		flt mind = numeric_limits<flt>::max();
		str minName;
		for(int p = 0; p != P; ++p) {
			str name;
			flt d;
			si R;
			getline(in,name);
			in>>d>>R; in.ignore();
			for(int r = 0; r != R; ++r) getline(in,tmp);

			if(R>maxR){
				maxR=R;
				mind=d;
				minName=move(name);
			}else if(R==maxR && d<mind){
				mind=d;
				minName=move(name);
			}
		}

		++k;
		if(k!=1)out<<"\n";
		out<<"RFP #"<<k<<"\n"<<minName<<"\n";
	}
}
