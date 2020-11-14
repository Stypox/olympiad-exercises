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

struct Point {
    int x,y;
};

struct Range {
    int yfrom, yto, x;
    Range(int a, int b, int c) : yfrom(a), yto(b), x(c) {
        assert(yfrom < yto);
    }

    int lunghezza() const {
        return yto - yfrom;
    }
};

bool comp(Point& a, Point& b) {
    return a.y < b.y;
}

int32_t main() {
	int N;
    in >> N;

    vector<Point> points(N);
    for (int n=0; n<N; ++n) {
        in>>points[n].x>>points[n].y;
    }

    auto it = min_element(points.begin(), points.end(), comp);
    if (it == points.begin()) {
        if (points[0].y != points[1].y) {
            // quindi il primo punto deve essere uguale all'ultimo
            // --> muovi l'ultimo punto all'inizio
            vector<Point> newPoints {points.back()};
            newPoints.insert(newPoints.end(), points.begin(), points.end() - 1);
            points = newPoints;
        }
    } else {
        vector<Point> newPoints {it, points.end()};
        newPoints.insert(newPoints.end(), points.begin(), it);
        points = newPoints;
    }
    points.push_back(points[0]);
    points.push_back(points[1]);

    vector<Range> ranges;
    int area = 0;
    for (int i=0;i<N+1;++i) {
        if (points[i].x == points[i+1].x) {
            if (points[i+1].y > points[i].y) {
                ranges.push_back(Range{points[i].y, points[i+1].y, points[i].x});
            } else {
                while(!ranges.empty()) {
                    Range& r = ranges.back();
                    if (points[i+1].y <= r.yfrom) {
                        // prendilo tutto
                        area += r.lunghezza() * (points[i].x - r.x);
                        ranges.pop_back();
                    } else {
                        // prendine parte
                        area += (r.yto - points[i+1].y) * (points[i].x - r.x);
                        r.yto = points[i+1].y;
                        break;
                    }
                }
            }
        }
    }

    out<<area<<"\n";
}
