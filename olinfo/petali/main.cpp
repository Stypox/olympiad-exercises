#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

struct Divisor {
	int v, biggerPos=-1;
	vector<bool> doable;

	Divisor(int val)
		: v{val}, doable(val, true) {};
};

vector<Divisor> getDivisors(int N) {
	vector<Divisor> divisors;
	for (int n=1;n<sqrt(N);++n) {
		if (N % n == 0) divisors.push_back(n);
	}

	int divisorsCount=divisors.size();
	if (int v = (int)(sqrt(N) + 0.5); v*v == N) {
		divisors.push_back(v);
	}

	for (int i=divisorsCount-1;i>0;--i) {
		divisors.push_back(N / divisors[i].v);
	}

	for(int i = 0; i != divisors.size(); ++i) {
		for(int j = i+1; j != divisors.size(); ++j) {
			if (divisors[j].v % divisors[i].v == 0) {
				divisors[i].biggerPos = j;
				break;
			}
		}
	}

	return divisors;
}

int solve(int N, int* S) {
	auto divisors = getDivisors(N);

	int res=0;
	for(int d=0;d<divisors.size();++d) {
		Divisor& div=divisors[divisors.size()-1-d];
		if (div.biggerPos==-1) {
			for (int starti=0;starti<div.v;++starti){
				int start=S[starti];

				for(int i=starti+div.v; i < N; i+=div.v) {
					if (S[i]!=start) {
						div.doable[starti]=false;
						break;
					}
				}

				res+=div.doable[starti];
			}
		} else {
			for (int starti=0;starti<div.v;++starti){
				int start=S[starti];
				const Divisor& biggerDiv = divisors[div.biggerPos];

				for (int i=starti; i<biggerDiv.v; i+=div.v) {
					if (S[i]!=start || !biggerDiv.doable[i]) {
						div.doable[starti]=false;
						break;
					}
				}

				res+=div.doable[starti];
			}
		}
	}
	return res;
}

int main() {
	int N;
	in>>N;

	int* arr = new int[N];
	for(int n = 0; n != N; ++n) {
		in>>arr[n];
	}
	out<<solve(N, arr);
	delete arr;
}