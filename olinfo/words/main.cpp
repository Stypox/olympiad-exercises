#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<")";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<" ";}deb(args...);}
#else
#define deb(...)
#endif

char numToChar(int16_t num, int8_t pos) {
	if (pos == 0) return (num & 0b11111) + 'a';
	if (pos == 1) return ((num >> 5) & 0b11111) + 'a';
	return ((num >> 10) & 0b11111) + 'a';
}

string numToStr(int16_t num) {
	return string{numToChar(num, 2), numToChar(num, 1), numToChar(num, 0)};
}

signed main() {
	int N,L,K;
	in>>N>>L>>K;

	vector<uint16_t> words;
	array<array<vector<uint8_t>, 26>, 26> byFirst2{};
	for(int k=0;k<K;++k){
		char a,b,c;
		in.ignore();
		in>>a>>b>>c;

		words.push_back(((a-'a')<<10) + ((b-'a')<<5) + (c-'a'));
		byFirst2[a-'a'][b-'a'].push_back(c-'a');
	}

	sort(words.begin(), words.end());
	for(auto& u:byFirst2) for(auto& v:u) sort(v.begin(), v.end());

	array<array<vector<int>, 26>, 26> mem;
	for(auto& a1:mem) for (auto& a2:a1) a2.resize(L, -1);

	function<int(int, uint8_t, uint8_t, int)> modes = [&](int i, uint8_t lastLast, uint8_t last, int remaining) -> int {
		if (i >= L) return 1;
		if (mem[lastLast][last][i] != -1) return mem[lastLast][last][i];

		int tot=0;
		for(auto next : byFirst2[lastLast][last]) {
			if(tot>=remaining) break;
			tot+=modes(i+1, last, next, remaining-tot);
		}

		mem[lastLast][last][i] = tot;
		return tot;
	};

	function<string(int i, uint8_t, uint8_t, int)> nth_string = [&](int i, uint8_t lastLast, uint8_t last, int remaining) -> string {
		if (i >= L) return "";

		int tot=0;
		for(auto next : byFirst2[lastLast][last]) {
			tot+=modes(i+1, last, next, remaining-tot);
			if(tot>=remaining) {
				return string{numToChar(next, 0)} + nth_string(i+1, last, next,
					remaining-tot+modes(i+1, last, next, remaining-tot));
			}
		}
	};

	int tot=0;
	string res;
	for(auto word : words) {
		uint8_t second = (word >> 5) & 0b11111, third = word & 0b11111;

		tot+=modes(3, second, third, N-tot);
		if(tot>=N) {
			res=numToStr(word) + nth_string(3, second, third, N-tot+modes(3, second, third, N-tot));
			break;
		}
	}

	out<<res;
}
