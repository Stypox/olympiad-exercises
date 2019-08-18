#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define inline inline __attribute__((always_inline))

using si = int_fast32_t;
using ui = uint_fast32_t;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr inline void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr inline void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

struct SegmentTree {
	vec<vec<ui>> layers;

	inline SegmentTree(vec<ui>&& init) {
		layers.emplace_back(init);

		while(layers.back().size()!=1){
			layers.push_back(vec<ui>(layers.back().size()/2 + layers.back().size()%2));
		}
		updateLayer(1,0,layers.at(1).size());
		sdeb();
	}

	inline void updateLayer(const si i, const si a, const si b) {
		if(i>=(si)layers.size()) return;

		for(int p = a*2; p<2*b; p+=2) {
			if(p==((si)layers.at(i-1).size()-1)){
				layers.at(i).at(p/2)=layers.at(i-1).at(p);
				break;
			} else {
				layers.at(i).at(p/2)=layers.at(i-1).at(p)+layers.at(i-1).at(p+1);
			}
		}

		updateLayer(i+1,a/2,(b+1)/2);
	}

	inline void sdeb() {
	#ifndef ONLINE_JUDGE
		for(int i = 0; i != layers.size(); ++i) {
			debc(layers.at(i), "Layer " + to_string(i) + ": ", setw(std::pow(2,i)*2));
		}
	#endif
	}

	inline si boundLeft(const si l, const si section) {
		return (1<<l)*section;
	}
	inline si boundRight(const si l, const si section) {
		return min((1<<l)*(section+1)-1, (si)(layers.at(0).size()-1));
	}

	si getr(const si l, const si section, const si a, const si b) {
		si bl=boundLeft(l,section), br=boundRight(l,section);
		if(a>br || b<bl) return 0;
		if(bl>=a && br<=b) return layers.at(l).at(section);

		si p1=getr(l-1, section*2,   a, b);
		si p2=getr(l-1, section*2+1, a, b);

		return p1+p2;
	}

	inline si getr(const si a, const si b) {
		return getr(layers.size()-1,0,a,b);
	}

	template<class F>
	inline void setr(const si a, const si b, const F& func) {
		for(si i = a; i <= b; ++i) {
			func(layers.at(0).at(i));
		}
		updateLayer(1,a/2,(b+2)/2);
		sdeb();
	}
};

int main() {
	ui T;
	in >> T;

	for(ui t = 0; t != T; ++t) {
		out<<"Case "<<t+1<<":\n";
		ui M;
		in>>M;
		
		vec<ui> pirates;
		for(ui m = 0; m != M; ++m) {
			ui N;
			in>>N;
			in.ignore();

			vec<ui> curr;
			ch c=in.get();
			while(c!='\n') {
				curr.push_back(c=='1');
				c=in.get();
			}

			for(ui n = 0; n != N; ++n) {
				pirates.insert(pirates.end(), curr.begin(), curr.end());
			}
		}

		SegmentTree st{move(pirates)};
		ui Q;
		in>>Q;

		ui count=1;
		for(ui q = 0; q != Q; ++q) {
			ch action;
			ui a,b;
			in>>action>>a>>b;

			if(action=='F'){
				st.setr(a,b,[](ui& v){v=1;});
			} else if(action=='E'){
				st.setr(a,b,[](ui& v){v=0;});
			} else if(action=='I'){
				st.setr(a,b,[](ui& v){v=!v;});
			} else{
				out<<"Q"<<count<<": "<<st.getr(a,b)<<"\n";
				++count;
			}
		}
		deb();
	}
}
