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

	nums.back().low = 0;
	nums.back().up = nums.back().m;

	for(int i = N-2; i >= 0; --i) {
		auto& el0 = nums[i], & el1 = nums[i+1];
		el0.low = max(0L, 2*el0.m - el1.up);
		el0.up = min(el0.m, 2*el0.m - el1.low);
	}

	out << nums[0].up - 2*nums[0].m+nums[1].up + 1;
}