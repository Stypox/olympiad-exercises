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

int main() {
	si t=0;
	while(1) {
		si N;
		in>>N;
		if(N==0)break;

		if(t!=0) out<<"\n";
		++t;

		vec<si> bags(N);
		for(auto&& bag : bags) {
			in>>bag;
		}
		sort(bags.rbegin(), bags.rend());

		si K=0, currk, last=numeric_limits<si>::max();
		for(auto&& bag : bags) {
			if (bag!=last) {
				currk=0;
				last=bag;
			}
			++currk;
			K=max(K,currk);
		}

		vec<vec<si>> res(K);
		si i=0;
		for(auto&& bag : bags) {
			res[i].push_back(bag);
			++i;
			i=(i%K);
		}

		out<<K<<"\n";
		for(auto&& rs : res) {
			out<<rs[0];
			for(si i = 1; i != rs.size(); ++i) {
				out<<" "<<rs[i];
			}
			out<<"\n";
		}
	}
}
