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

struct FTD {
	map<si,si> counts;
	FTD() = default;

	FTD operator+(const FTD& other) {
		FTD ftd{};
		ftd.counts = counts;
		ftd += other;
		return ftd;
	}
	void operator+=(const FTD& other) {
		for(auto&& c : other.counts) {
			counts[c.first] += c.second;
		}
	}

	FTD operator-(const FTD& other) {
		FTD ftd{};
		ftd.counts = counts;
		ftd -= other;
		return ftd;
	}
	void operator-=(const FTD& other) {
		for(auto&& c : other.counts) {
			counts[c.first] -= c.second;
		}
	}
};

constexpr si lsOne(si i) {
	return i & (-i);
}

struct FenwickTree {
	vec<FTD> data;

	FenwickTree(si N) : data(N+1) {}
	
	FTD query(si i) {
		FTD sum;
		for(; i!=0; i-=lsOne(i))
			sum += data[i];
		return sum;
	}

	FTD query(si a, si b) {
		return query(b) - query(a-1);
	}

	void set(si i, si val) {
		for(; i<=data.size(); i+=lsOne(i))
			data[i].counts[val]++;
	}
};

int main() {
	while(1) {
		si N,Q;
		in>>N>>Q;
		if(N==0 || (!in)) break;

		FenwickTree ft{N};
		for(int n = 1; n <= N; ++n) {
			si val;
			in>>val;
			ft.set(n, val);
		}

		for(int q = 0; q != Q; ++q) {
			si a,b;
			in>>a>>b;

			FTD res = ft.query(a,b);
			si el = max_element(res.counts.begin(), res.counts.end(), [](const pair<si,si>& f1, const pair<si,si>& f2) { return f1.second < f2.second; })->second;

			out<<el<<"\n";
		}
	}
}
