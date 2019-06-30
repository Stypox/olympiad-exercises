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

enum Dir:signed char{pX=3,pY=5,pZ=7,mX=-3,mY=-5,mZ=-7,No=0};
Dir dirFromStr(str s) {
	if(s=="No") return No;
	if(s=="+y") return pY;
	if(s=="-y") return mY;
	if(s=="+z") return pZ;
	if(s=="-z") return mZ;
}
str dirToString(Dir d) {
	switch(d){
		case pX: return "+x";
		case mX: return "-x";
		case pY: return "+y";
		case mY: return "-y";
		case pZ: return "+z";
		case mZ: return "-z";
	}
}
Dir rotate(Dir curr, Dir d) {			
	switch(curr){
		case pX:
			switch(d){
				case pY: return pY;
				case mY: return mY;
				case pZ: return pZ;
				case mZ: return mZ;
			}
		case mX:
			switch(d){
				case pY: return mY;
				case mY: return pY;
				case pZ: return mZ;
				case mZ: return pZ;
			}
		case pY:
			switch(d){
				case pY: return mX;
				case mY: return pX;
				case pZ: return pY;
				case mZ: return pY;
			}
		case mY:
			switch(d){
				case pY: return pX;
				case mY: return mX;
				case pZ: return mY;
				case mZ: return mY;
			}
		case pZ:
			switch(d){
				case pY: return pZ;
				case mY: return pZ;
				case pZ: return mX;
				case mZ: return pX;
			}
		case mZ:
			switch(d){
				case pY: return mZ;
				case mY: return mZ;
				case pZ: return pX;
				case mZ: return mX;
			}
	}
}

int main() {
	while(1) {
		si L;
		in>>L;
		if(L==0)break;

		vec<Dir> dirs;
		for(int l = 0; l != L-1; ++l) {
			str tmp;
			in>>tmp;
			dirs.push_back(dirFromStr(tmp));
		}

		Dir currDir = pX;
		for(auto d : dirs) {
			if(d != No) {
				deb(dirToString(currDir), dirToString(d), "=");
				currDir=rotate(currDir,d);
				deb(dirToString(currDir),"\n");
			}
		}

		deb(dirToString(currDir), "  <-\n\n\n");
		out<<dirToString(currDir)<<"\n";
	}
}
