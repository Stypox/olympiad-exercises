#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using str = string;
using hash_t = pair<ui,ui>;
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

constexpr ui P1=47, P2=59, M=100000007;

template<ui P>
array<ui, 50010> powP() {
	array<ui, 50010> result;
	ui now=1;
	for(int n=0;n<50010;++n){
		result[n]=now;
		now*=P;
		now%=M;
	}
	return result;
}
array<ui, 50010> powP1 = powP<P1>(), powP2 = powP<P2>();

template<ui P>
ui getHash(const char* s, si l) {
	if(l==0) return 0;
	return ((P*getHash<P>(s,l-1))%M + s[l-1])%M;
}

template<ui P>
ui moveHash(ui h, si l, char removed, char added) {
	ui power=(P==P1 ? powP1[l] : powP2[l]);
	deb(h*P, removed*power, (int)added);
	return (M + h*P - (removed*power)%M + added)%M;
}

vec<hash_t> getHashes(const char* s, si N, si l){
	vec<hash_t> res;
	res.push_back({getHash<P1>(s,l), getHash<P2>(s,l)});

	for(si n=0;n<(N-l);++n){
		auto[h1,h2]=res.back();
		res.push_back({moveHash<P1>(h1,l,s[n],s[n+l]),
		               moveHash<P2>(h2,l,s[n],s[n+l])});
	}

	return res;
}

bool hasDuplicates(vec<hash_t>& hashes) {
	sort(hashes.begin(), hashes.end());

	hash_t last=hashes[0];
	for(si i=1;i<hashes.size();++i){
		if (hashes[i]==last) return true;
		last=hashes[i];
	}
	return false;
}

#ifdef DEBUG
vec<hash_t> getHashesBrutto(const char* s, si N, si l){
	vec<hash_t> res;
	for(si n=0;n<(N-l);++n){
		res.push_back({getHash<P1>(s+n,l), getHash<P2>(s+n,l)});
	}

	return res;
}

void prHashes(const vec<hash_t>& hashes) {
	for(auto&& h:hashes) cout<<"{"<<h.first<<" "<<h.second<<"}  "; cout<<"\n";
}
#endif

int main() {
	si N; str s;
	in>>N>>s;
	for(char& chr:s) chr-='a', deb((int)chr);

	si a=0,b=N;
	while(a!=(b-1)){
		si l = (a+b)/2;
		deb(a,b,l, powP1[l-1], powP2[l-1]);

		vec<hash_t> hashes=getHashes(s.c_str(),N,l);
		//prHashes(hashes); prHashes(getHashesBrutto(s.c_str(),N,l));

		if(hasDuplicates(hashes)) {
			deb("yes!\n");
			a=(a+b)/2;
		} else {
			deb("no :-(\n");
			b=(a+b)/2;
		}
	}

	deb(moveHash<P1>(19, 2, 18, 11));
	out<<a<<"\n";
}
