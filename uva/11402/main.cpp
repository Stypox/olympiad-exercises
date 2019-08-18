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
template<class T> constexpr void debc(const T&, str="", str="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T> constexpr void debc(const T& t, str pre="", str sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

struct SegmentTree {
	vec<vec<si>> layers;

	SegmentTree(const vec<si>& init) {
		layers.push_back(init);

		while(layers.back().size()!=1){
			layers.push_back(vec<si>(layers.back().size()/2 + layers.back().size()%2));
		}
		updateLayer(1,0,layers[1].size());
		sdeb();
	}

	void updateLayer(si i, si a, si b) {
		deb(i,a,b);
		if(i>=layers.size()) return;

		for(int p = a*2; p<2*b; p+=2) {
			if(p<(layers[i-1].size()-1)){
				layers[i][p/2]=layers[i-1][p]+layers[i-1][p+1];
			} else if(p==(layers[i-1].size()-1)){
				layers[i][p/2]=layers[i-1][p];
				break;
			} else {
				break;
			}
		}

		updateLayer(i+1,a/2,(b+1)/2);
	}

	void sdeb() {
		for(int i = 0; i != layers.size(); ++i) {
			debc(layers[i], "Layer " + to_string(i) + ": ");
		}
	}

	static si lowerMultiple(si b,si lsize){
		if((b%lsize)==0) return b-lsize;
		return b-(b%lsize);
	}

	si getr(si a, si b, si l) {
		if(a>=b||b>layers[0].size())return 0;
		si lsize=1<<l;
		si half=lsize-(a%lsize)+a;
		deb("l",l,"lsize",lsize,"half",half,"a,b",a,b);

		if((a%lsize)==0){
			deb("A");
			if(b >= (a+lsize)){
				deb("a");
				return layers[l][a/lsize] + getr(half,b,l-1);
			}
		}
		if((b%lsize)==0 || b==layers[0].size()){
			deb("B",lowerMultiple(b,lsize));
			if(a <= lowerMultiple(b,lsize)){
				deb("b");
				return getr(a,half,l-1) + layers[l][(b-!(b%lsize))/lsize];
			}
		}

		deb("C");
		if(half>=b) return getr(a,b,l-1);
		deb("D");
		return getr(a,half,l-1) + getr(half,b,l-1);
	}

	si getr(si a, si b) {
		return getr(a,b+1,layers.size()-1);
	}

	template<class F>
	void setr(si a, si b, F func) {
		for(int i = a; i <= b; ++i) {
			func(layers[0][i]);
		}
		updateLayer(1,a/2,(b+2)/2);
		sdeb();
	}
};

int main() {
	si T;
	in >> T;

	for(int t = 0; t != T; ++t) {
		out<<"Case "<<t+1<<":\n";
		si M;
		in>>M;
		
		vec<si> pirates;
		for(int m = 0; m != M; ++m) {
			si N;
			str desc;
			in>>N>>desc;

			vec<si> curr;
			for(auto&& ch : desc) {
				curr.push_back((si)(ch=='1'));
			}

			for(int n = 0; n != N; ++n) {
				pirates.insert(pirates.end(), curr.begin(), curr.end());
			}
		}

		SegmentTree st{pirates};		
		si Q;
		in>>Q;

		si count=1;
		for(int q = 0; q != Q; ++q) {
			ch action;
			si a,b;
			in>>action>>a>>b;

			if(action=='F'){
				st.setr(a,b,[](si& v){v=1;});
			} else if(action=='E'){
				st.setr(a,b,[](si& v){v=0;});
			} else if(action=='I'){
				st.setr(a,b,[](si& v){v=!v;});
			} else{
				out<<"Q"<<count<<": "<<st.getr(a,b)<<"\n";
				++count;
			}
		}
	}
}
