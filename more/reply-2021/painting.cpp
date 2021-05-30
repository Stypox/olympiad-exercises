#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Point {
	float x,y;
};

struct Retta {
	float m, q;
	bool seen = false;
	Retta(float m1, float q1) : m{m1}, q{q1} {}

	float f(float x) {
		return m*x + q;
	}
	float inverse(float x) {
		return (x - q)/m;
	}

	bool intersects(Retta& r) {
		return m != r.m;
	}
	float xIntersect(Retta& r) {
		return (r.q-q)/(m-r.m);
	}
};

tuple<int, float, int, float> xNearestTo(float xPartenza, vector<Retta>& rette) {
	int iSx=-1, iDx=-1;
	float xSx=numeric_limits<float>::min(), xDx=numeric_limits<float>::max();
	for(int n=1;n<rette.size();++n){
		if (!rette[n].seen && rette[0].intersects(rette[n])) {
			float x = rette[0].xIntersect(rette[n]);
			if (x < xPartenza) {
				if (x > xSx) {
					xSx = x;
					iSx = n;
				}
			} else {
				if (x < xDx) {
					xDx = x;
					iDx = n;
				}
			}
		}
	}
	return {iSx, xSx, iDx, xDx};
}

signed main() {
	int T;
	in>>T;
	for(int t=0;t<T;++t){
		int N;
		in>>N;

		if (N <= 2) {
			// esci
		}

		vector<Retta> rette(N);
		for (int n=0;n<N;++n){
			in>>rette[n].m>>rette[n].q;
		}
		rette[0].seen = true;

		sort(rette.begin(), rette.end(), [](Retta&a,Retta&b){
			return abs(a.f(0)) < abs(b.f(0));
		});

		float xPartenza = rette[0].inverse(0);
		auto [aiSx, axSx, aiDx, axDx] = xNearestTo(xPartenza, rette);
		vector<Point> points;

		points.emplace_back(axSx, rette[0].f(axSx));
		rette[aiSx].seen = true;

		int iPrevPrev=0, iPrev=aiSx;
		while(1) {
			auto [iSx, xSx, iDx, xDx] = xNearestTo(points.back().x, rette);
			Retta nuova = rette[iPrevPrev];

		}
	}
}
