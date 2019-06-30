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
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si pointer=0;
		array<si,100> bytes{};
		for(auto& b:bytes) b=0;
		
		str cmd;
		in>>cmd;

		for(auto c : cmd){
			switch(c){
				case '.': break;
				case '>': { ++pointer; if(pointer>=100) pointer=0; break; }
				case '<': { --pointer; if(pointer<=-1) pointer=99; break; }
				case '+': { ++bytes[pointer]; if(bytes[pointer]>=256) bytes[pointer]=0; break; }
				case '-': { --bytes[pointer]; if(bytes[pointer]<=-1) bytes[pointer]=255; break; }
			}
		}

		// --- not working for some reason ---
		// out<<"Case "<<t+1<<":"<<setbase(16)<<noshowbase<<uppercase;
		// for(auto b:bytes) {
		// 	out<<" "<<setw(2)<<setfill('0')<<b;
		// }
		// out<<"\n";

		out<<"Case "<<t+1<<":";
		for(auto b:bytes) {
			printf(" %02X", b);
		}
		out<<"\n";
	}
}
