#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = int_fast32_t;
using ui = uint_fast32_t;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;
#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=str, class S=str> constexpr void debc(const T&, P="", S="") {}
#define at operator[]
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=str, class S=str> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

enum Action : char {
	nothing=0,
	set=1,
	unset=2,
	flip=3,
};

struct SegmentTree {
	ui n;
	vec<ui> nodes;
	vec<Action> actions;
	
	void build(const ui i, const ui L, const ui R, const vec<ui>& init) {
		if (L==R) {
			nodes.at(i)=init.at(L);
		} else {
			build(2*i,     L,           (L+R)/2, init);
			build(2*i + 1, (L+R)/2 + 1, R,       init);
			nodes.at(i) = nodes.at(i*2) + nodes.at(i*2 + 1);
		}
	}

	ui query(const ui i, const ui L, const ui R, const ui a, const ui b) {
		applyAct(i, L, R);
		if (L>b || R<a) return 0;
		if (L>=a && R<=b) return nodes.at(i);

		si s1 = query(i*2,      L,          (L+R)/2, a, b);
		si s2 = query(i*2 + 1, (L+R)/2 + 1, R,       a, b);
		return s1+s2;
	}

	void change(Action& curr, Action action) {
		if (action==Action::flip) {
			switch(curr){
			case Action::nothing:
				curr=Action::flip;
				break;
			case Action::set:
				curr=Action::unset;
				break;
			case Action::unset:
				curr=Action::set;
				break;
			case Action::flip:
				curr=Action::nothing;
				break;
			}
		} else if (action!=Action::nothing) {
			curr=action;
		}
	}

	void applyAct(const ui i, const ui L, const ui R) {
		Action& action = actions.at(i);
		deb("apply",i,L,R,action);
		
		switch(action){
		case Action::nothing:
			action=Action::nothing;
			return;
		case Action::set:
			nodes.at(i) = R-L+1;
			break;
		case Action::unset:
			nodes.at(i) = 0;
			break;
		case Action::flip:
			nodes.at(i) = R-L+1-nodes.at(i);
			break;
		}
		debc(nodes);

		if (i*2<actions.size()) {
			change(actions.at(i*2), action);
			change(actions.at(i*2 + 1), action);
		}
		action=Action::nothing;
	}

	template<Action action>
	void act(const ui i, const ui L, const ui R, const ui a, const ui b) {
		deb("act",i,L,R);
		if (L>b || R<a) {
			applyAct(i, L, R);
			return;
		}

		if (L>=a && R<=b) {
			deb("a");
			change(actions.at(i), action);
			applyAct(i, L, R);
			return;
		}
		deb("b");
		applyAct(i, L, R);

		act<action>(i*2,     L,           (L+R)/2, a, b);
		act<action>(i*2 + 1, (L+R)/2 + 1, R,       a, b);
		nodes.at(i) = nodes.at(i*2) + nodes.at(i*2 + 1);
		deb("c", i, nodes.at(i));
	}

public:
	SegmentTree(const vec<ui>& init) :
			n{init.size()}, nodes(4*n, 0), actions(4*n, Action::nothing) {
		build(1, 0, n-1, init);
	}

	ui query(const ui a, const ui b) {
		return query(1, 0, n-1, a, b);
	}

	void set0(const ui a, const ui b) {
		return act<Action::unset>(1, 0, n-1, a, b);
	}
	void set1(const ui a, const ui b) {
		return act<Action::set>(1, 0, n-1, a, b);
	}
	void flip(const ui a, const ui b) {
		return act<Action::flip>(1, 0, n-1, a, b);
	}

	void sdeb() {
		debc(nodes,   "nodes:   ");
		debc(actions, "actions: ");
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

		SegmentTree st{pirates};
		st.sdeb();

		ui Q, query=1;
		in>>Q;
		for(ui q = 0; q != Q; ++q) {
			ch action;
			ui a,b;
			in>>action>>a>>b;

			if(action=='F'){
				st.set1(a,b);
			} else if(action=='E'){
				st.set0(a,b);
			} else if(action=='I'){
				st.flip(a,b);
			} else{
				out<<"Q"<<query<<": "<<st.query(a,b)<<"\n";
				++query;
			}
			deb(action, a, b);
			st.sdeb();
		}
		deb();
	}
}
