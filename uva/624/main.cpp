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

si countOnes(si i) {
	si cnt=0;
	while (i!=0) {
		cnt += (bool)(i&1);
		i>>=1;
	}
	return cnt;
}

int main() {
	while(1) {
		si N,M;
		in>>N>>M;
		if(!in) break;
		
		vec<si> CD(M);
		for(auto&& m : CD)
			in>>m;
		
		si bestSum=-1, bestI, bestIOnes=-1;
		for(int i = 0; i != (1<<M); ++i) {
			si sum=0;
			for(int m = 0; m != M; ++m)
				if (i & (1<<m))
					sum+=CD[m];
			
			si iOnes=-1;
			if(sum<=N && (sum>bestSum || (sum==bestSum && (iOnes=countOnes(i))>bestIOnes))) {
				bestSum=sum;
				bestI=i;
				bestIOnes=(iOnes==-1 ? countOnes(i) : iOnes);
			}
		}

		for(int m = 0; m != M; ++m)
			if (bestI & (1<<m))
				out<<CD[m]<<" ";
		out<<"sum:"<<bestSum<<"\n";
	}
}
