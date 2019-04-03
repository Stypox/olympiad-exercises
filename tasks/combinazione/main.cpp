#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = int64_t;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

struct Num {
	si m, low, up;
};

int main() {
	si N;
	in>>N;

	vec<Num> nums(N);
	for(auto&& num : nums)
		in>>num.m;

	nums.back().low = numeric_limits<si>::min()/2;
	nums.back().up = nums.back().m;

	for(int i = N-2; i >= 0; --i) {
		nums[i].low = 2*nums[i].m - nums[i+1].up;
		nums[i].up = min(nums[i].m, 2*nums[i].m - nums[i+1].low);
	}

	out << nums[0].up-nums[0].low+1;
}