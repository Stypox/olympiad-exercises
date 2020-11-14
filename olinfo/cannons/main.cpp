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

struct Conn {
    int to, w;
};

struct Node {
    int minSoFar = numeric_limits<int>::max();
    int to;
};

struct Point {
    int at, val;
};

int32_t main() {
	int N;
    in>>N;

    vector<Node> nodes(N);
    for (int n=0;n<N-1;++n) {
        in>>nodes[n].to;
    }

    auto compare = [](Point&a,Point&b) { return a.val > b.val; };
    priority_queue<Point, vector<Point>, decltype(compare)> pq(compare);
    pq.push(Point{0, 0});
    while (!pq.empty()) {
        auto [at, val] = pq.top();
        pq.pop();

        if (val < nodes[at].minSoFar) {
            nodes[at].minSoFar = val;
            pq.push(Point{nodes[at].to, val});
            if (at != N-1) {
                pq.push(Point{at+1, val+1});
            }
            if (at != 0) {
                pq.push(Point{at-1, val+1});
            }
        }
    }

    out<<nodes.back().minSoFar<<"\n";
}
