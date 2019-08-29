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

void printPred(const vec<si>& pred, const vec<si>& nums, si i) {
	if (i>=0) {
		printPred(pred, nums, pred[i]);
		out<<nums[i]<<"\n";
	}
}

int main() {
	vec<si> nums;
	while(1) {
		si n;
		in>>n;
		if(!in) break;
		nums.push_back(n);
	}
	
	vec<si> pred(nums.size(), -1);
	vec<si> lis(nums.size());
	vec<pair<si,si>> mins;

	lis[0]=1;
	mins.push_back({nums[0], 0});

	auto binSearch = [&](si el) {
		si besti=-1,a=0,b=mins.size();
		while(1) {
			si m=(a+b)/2;
			if(mins[m].first<el) {
				besti=max(m, besti);
				a=m+1;
			} else {
				b=m;
			}

			if(a>=b) break;
			if(a>=b) {
				if (a==b && b!=mins.size() && mins[b].first<el)
					besti=max(b,besti);
				break;
			}
		}
		return besti;
	};

	for(int n = 1; n != nums.size(); ++n) {
		si maxlis = binSearch(nums[n]);
		lis[n] = maxlis+2;
		pred[n] = mins[maxlis].second;

		deb(maxlis, mins[maxlis].first, mins[maxlis].second);
		if (mins.size() <= maxlis+1) {
			mins.resize(maxlis+2);
			mins[maxlis+1] = {nums[n], n};
		} else if (nums[n] <= mins[maxlis+1].first) {
			mins[maxlis+1] = {nums[n], n};
		}
	}

	debc(pred);
	out<<mins.size()<<"\n-\n";
	printPred(pred, nums, mins.back().second);
}
