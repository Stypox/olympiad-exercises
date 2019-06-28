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
template<class... Ts> constexpr void deb(const Ts&...) {}
istream& in = std::cin;
ostream& out = std::cout;
#else
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
ifstream in{"input.txt"};
ofstream out{"output.txt"};
#endif

int main() {
	while(1){
		si dur,N;
		flt down,owed;
		in>>dur>>down>>owed>>N;
		if(dur<0)break;

		si m=0,next;
		flt depr,value=owed+down,loan=owed/dur;
		in>>next; // == 0 useless

		for(int n = 0; n != N; ++n) {
			in>>depr;
			if(n==(N-1)) next=numeric_limits<si>::max();
			else in>>next;

			while(m<next){
				value-=depr*value;
				if(owed<value){
					if(m==1) out<<m<<" month\n";
					else out<<m<<" months\n";
					m=numeric_limits<si>::max();
					break;
				}
				owed-=loan;
				++m;
				deb("m",m,"value",value,"owed",owed,"depr",depr,"loan",loan);
			}
		}
	}
}
