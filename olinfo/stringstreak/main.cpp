#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

int32_t main() {
	string s;
	int B;
	in>>s>>B;
	int N=s.size();

	int maxLen=-1;
	for (char i='a'; i<='z'; ++i) {
		deb(i);
		int from=0, to=0, cost=0;
		deque<pair<char, int>> dq;
		bool closed=true;

		while(1) {
			while(cost<=B && to<N) {
				if (s[to] == i) {
					closed = true;
				} else {
					if (closed) {
						dq.push_back({s[to], 1});
						cost += 2;
						closed = false;
					} else {
						cost -= (1<<dq.back().second);
						dq.back().second++;
						cost += (1<<dq.back().second);
					}
				}
				++to;
			}
			//deb(from, to, cost);
			maxLen=max(maxLen, to-from-(cost>B));
			if (to==N) break;

			if (s[from]==i) {
				++from;
			} else {
				++from;
				cost -= (1<<dq.front().second);
				dq.front().second--;
				if (dq.front().second == 0) {
					dq.pop_front();
				} else {
					cost += (1<<dq.front().second);
				}
			}
		}
	}

	out<<maxLen<<"\n";
}
