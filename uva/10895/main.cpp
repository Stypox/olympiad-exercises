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

using si3 = tuple<si,si,si>;

int main() {
	while(1) {
		si M,N;//rows,cols
		in>>M>>N;
		if(!in) break;

		vec<si3> pts; 
		for(int m = 1; m <= M; ++m) {
			si R;
			in>>R;

			vec<si> idxs(R);
			for(int r = 0; r != R; ++r) {
				in>>idxs[r];
			}

			for(int r = 0; r != R; ++r) {
				si v;
				in>>v;
				pts.emplace_back(idxs[r],m,v);
			}
		}

		sort(pts.begin(), pts.end(), [](const si3& a, const si3& b){
			const si& ma = get<0>(a);
			const si& na = get<1>(a);
			const si& mb = get<0>(b);
			const si& nb = get<1>(b);

			if (ma==mb){
				return na<nb;
			}
			return ma<mb;
		});

		out<<N<<" "<<M<<"\n";
		vec<si3>::iterator begin=pts.begin(),end=pts.begin();
		for(int n = 1; n <= N; ++n) {
			while(end!=pts.end() && get<0>(*end)==n) ++end;

			out<<distance(begin,end);
			for(auto it = begin; it != end; ++it)
				out<<" "<<get<1>(*it);
			out<<"\n";

			for(auto it = begin; it != end; ++it) {
				if(it!=begin) out<<" ";
				out<<get<2>(*it);
			}
			out<<"\n";

			begin=end;
		}
	}
}
