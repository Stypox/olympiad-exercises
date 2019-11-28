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

struct Node {
	si tin = -1;
	si tout = -1;
	vec<si> conn;
};

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		si N,M;
		in>>N>>M;

		vec<Node> nodes(N);
		for(si m = 0; m != M; ++m) {
			si a,b;
			in>>a>>b; a--; b--;

			nodes[a].conn.push_back(b);
		}

		si time = 0;
		function<void(si)> dfsTout = [&nodes, &dfsTout, &time](si i) {
			if (nodes[i].tin != -1) return;
			nodes[i].tin=time++;
			
			for(auto&& con : nodes[i].conn) {
				dfsTout(con);
			}

			nodes[i].tout=time++;
		};

		for(si n=0; n<N; ++n) {
			dfsTout(n);
		}


		function<void(si)> dfsRemove = [&nodes, &dfsRemove](si i) {
			if (nodes[i].tout == -1) return;
			nodes[i].tout=-1;
			
			for(auto&& con : nodes[i].conn) {
				dfsRemove(con);
			}
		};
		
		vector<si> all(N);
		iota(all.begin(), all.end(), 0);
		sort(all.begin(), all.end(), [&nodes](si a,si b){return nodes[a].tout > nodes[b].tout;});
		
		si count = 0;
		for(si n=0; n<N; ++n) {
			if (nodes[all[n]].tout != -1) {
				dfsRemove(all[n]);
				++count;
			}
		}
		out<<count<<"\n";
	}
}
