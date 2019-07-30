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

int main() {
	while(1) {
		str line;
		getline(in, line);
		if(line == "") break;

		list<ch> chars;

		list<ch>::iterator ptr=chars.begin();
		for(auto&& c : line) {
			if(c=='[') {
				ptr=chars.begin();
			}else if(c==']'){
				ptr=chars.end();
			}else{
				ptr=chars.insert(ptr, c);
				++ptr;
			}
		}

		for(auto&& c : chars) {
			out<<c;
		}
		out<<"\n";
	}
}
