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

int main() {
	out<<fixed<<setprecision(3);
	while(1) {
		si lastkm=0, consumption=0, leaks=0;
		flt fuel=0, minfuel=1;

		while(1) {
			si km;
			str type;
			in>>km>>type;
			
			fuel -= (km-lastkm)*(consumption/((flt)100) + leaks);
			if (fuel < minfuel) minfuel = fuel;
			lastkm=km;

			if (type=="Fuel") {
				in>>type>>consumption;
				if (consumption==0) return 0;
			} else if (type=="Goal") {
				break;
			} else if (type=="Leak") {
				++leaks;
			} else if (type=="Gas") {
				in>>type;
				fuel=0;
			} else if (type=="Mechanic") {
				leaks=0;
			} else {
				assert(false);
			}
		}

		out<<-minfuel<<"\n";
	}
}
