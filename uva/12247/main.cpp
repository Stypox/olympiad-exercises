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
		array<si,3> sis, bro;
		array<bool,53> used; for(auto&&v:used)v=false;
		in>>sis[0]>>sis[1]>>sis[2]>>bro[0]>>bro[1];
		if(sis[0]==0)break;
		bro[2]=0;
		for(auto s:sis)used[s]=true;
		for(auto b:bro)used[b]=true;

		sort(sis.rbegin(), sis.rend());
		sort(bro.begin(), bro.end());

		auto mingreq = [&](si v){
			while(used[v]) {
				++v;
				if(v>52) return (si)53;
			}
			return v;
		};
		auto eval = [&](){
			si won=0;
			si pos0;
			if(bro[0]>sis[0]) ++won; else if(!bro[0])pos0=0;
			if(bro[1]>sis[1]) ++won; else if(!bro[1])pos0=1;
			if(bro[2]>sis[2]) ++won; else if(!bro[2])pos0=2;

			if(won==2) return mingreq(1);
			else if(won==1) return mingreq(sis[pos0]);
			else return (si)53;
		};

		si maxsofar=0;
		for (size_t i = 0; i < 6; i++) {
			for (size_t j = 0; j < 6; j++) {
				si v=eval();
				if(v>maxsofar) maxsofar=v;
				random_shuffle(sis.begin(),sis.end());
			}
			random_shuffle(bro.begin(),bro.end());
		}

		out<<(maxsofar>52?-1:maxsofar)<<"\n";
	}
}
