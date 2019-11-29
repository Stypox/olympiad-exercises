#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#endif

constexpr ui P=53, M=1000000007;

int main() {
	si N;
	in>>N;
	str s;
	in>>s;
	s.resize(N);

	for(char chr:s){
		chr-='a';
	}

	function<ui(si,si)> getHash = [&s, &getHash](si x, si l) {
		if(l==0) return (ui)0;
		return ((P*getHash(x,l-1))%M + s[x+l-1])%M;
	};
	auto powMod = [](si num, si to){
		ui res=1;
		for(si i=0;i<to;++i){
			res*=num;
			res%=M;
		}
		return res;
	};

	auto getHashes = [&s,&getHash,&powMod](si l){
		vector<ui> res;
		res.push_back(getHash(0,l));

		ui pexp=powMod(P,l);
		for(si i=0;i<s.size()-l-1;++i) {
			ui last=res.back();
			ui calc=(((last-s[i]*pexp)*P)%M + s[i+l]%M)%M;
			res.push_back(calc);
		}

		return res;
	};

	debc(getHashes(1));

	return 0;
	si a=0,b=s.size(),result;
	while(1) {
		deb(a,b);
		vec<ui> hashes = getHashes((a+b)/2);
		sort(hashes.begin(), hashes.end());
		debc(hashes);

		bool found=false;
		si last=hashes[0];
		for(int h=1;h<hashes.size();++h){
			if(hashes[h]==last) {
				found=true;
				break;
			}

			last=hashes[h];
		}

		if (found) {
			if(a==(b-1)) {
				result=a;
				break;
			}

			a=(a+b)/2;
		} else {
			if(a==(b-1)) {
				result=-1;
				break;
			}
			b=(a+b)/2;
		}
		deb();
	}

	out<<result;
}
