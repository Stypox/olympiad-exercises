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

struct Contestant {
	si c;
	bool encountered = false;
	vec<si> solved{};
	si time = 0;

	void update(si P, si T, ch L) {
		encountered = true;
		if (L == 'C') {
			//if (find(solved.begin(), solved.end(), P) == solved.end()) {
				solved.push_back(P);
				time += T;
			//}
		} else if (L == 'I') {
			time += 20;
		}
	}

	bool operator<(const Contestant& ct) {
		if (solved.size() == ct.solved.size()) {
			if (time == ct.time) {
				return c > ct.c;
			} else {
				return time > ct.time;
			}
		} else {
			return solved.size() < ct.solved.size();
		}
	}
};

int main() {
	si T;
	in >> T;
	in.ignore(2);
	
	for(int t = 0; t != T; ++t) {
		array<Contestant, 100> cts{};
		int ctn = 0;
		for(auto&& ct : cts) {
			++ctn;
			ct.c = ctn;
		}

		while (1) {
			str line;
			getline(in, line);
			if (line == "") break;

			int C, P, T; char L;
			sscanf(line.c_str(), "%d %d %d %c", &C,&P,&T,&L);
			cts[C-1].update(P,T,L);
		}

		sort(cts.rbegin(), cts.rend());
		for(auto&& ct : cts) {
			if (ct.encountered) {
				out<<ct.c<<" "<<ct.solved.size()<<" "<<ct.time<<"\n";
			}
		}
		out<<"\n";
	}
}
