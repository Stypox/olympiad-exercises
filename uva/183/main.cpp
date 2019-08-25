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
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

vec<vec<bool>> bitmap;

si bcount;
void B(si ra, si rb, si ca, si cb) {
	if(ra==rb || ca==cb) return;

	bool lastch=bitmap[ra][ca];
	bool allequal=true;
	for(int r = ra; r != rb; ++r)
		for(int c = ca; c != cb; ++c)
			if (bitmap[r][c] != lastch) {
				allequal=false;
				goto endloop;
			}
	endloop:

	if(bcount==50) {
		out<<"\n";
		bcount=0;
	}
	++bcount;

	if (allequal) {
		out<<lastch;
	} else {
		out<<'D';
		B(ra, (rb+ra+1)/2, ca, (cb+ca+1)/2);
		B(ra, (rb+ra+1)/2, (cb+ca+1)/2, cb);
		B((rb+ra+1)/2, rb, ca, (cb+ca+1)/2);
		B((rb+ra+1)/2, rb, (cb+ca+1)/2, cb);
	}
}

void D(si ra, si rb, si ca, si cb) {
	if(ra==rb || ca==cb) return;
	ch v=' ';
	while(isspace(v))
		v=in.get();
	if (v=='D') {
		D(ra, (rb+ra+1)/2, ca, (cb+ca+1)/2);
		D(ra, (rb+ra+1)/2, (cb+ca+1)/2, cb);
		D((rb+ra+1)/2, rb, ca, (cb+ca+1)/2);
		D((rb+ra+1)/2, rb, (cb+ca+1)/2, cb);
	} else {
		bool val = (v=='1');
		for(int r = ra; r != rb; ++r)
			for(int c = ca; c != cb; ++c)
				bitmap[r][c]=val;
	}
}

int main() {
	while(1) {
		ch type;
		while(isspace(type))
			type=in.get();
		si R,C;
		in>>type>>R>>C;
		if(type=='#') break;
		deb(type, R, C);

		bitmap.assign(R, vec<bool>(C, false));

		if (type=='B') {
			out<<'D'<<setw(4)<<R<<setw(4)<<C<<"\n";
			for(int r = 0; r != R; ++r) {
				for(int c = 0; c != C; ++c) {
					ch v=' ';
					while(isspace(v))
						v=in.get();
					bitmap[r][c]=(v=='1');
				}
			}

			bcount=0;
			B(0,R,0,C);
			out<<"\n";
		} else if (type=='D') {
			out<<'B'<<setw(4)<<R<<setw(4)<<C<<"\n";
			D(0,R,0,C);

			si count=0;
			for(int r = 0; r != R; ++r) {
				for(int c = 0; c != C; ++c) {
					out<<bitmap[r][c];
					++count;
					if (count==50) {
						out<<"\n";
						count=0;
					}
				}
			}
			if (count!=0) out<<"\n";
		} else {
			assert(false);
		}
	}
}
