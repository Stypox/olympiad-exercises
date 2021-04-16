#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

struct Node{
   int parent=-1;
   int invSotto;
   vector<pair<int,bool>> children; // false se direzione giusta
};

int32_t main() {
	int N;
	in>>N;
	vector<Node> nodes(N);
	for(int n=0;n<N-1;++n){
      int a,b;
      in>>a>>b;
      a--;b--;

      bool dir=true;
      if(nodes[b].parent==-1) { swap(a,b); dir=false; }
      nodes[a].parent=b;
      nodes[b].children.push_back({a,dir});
	}

	function<int(int)> dfs = [&](int i) {
      int res=0;
      for(auto [to, dir] : nodes[i].children) {
         res+=dir;
         res+=dfs(to);
      }
      nodes[i].invSotto=res;
      return res;
	};

   int root;
	for(int n=0;n<N;++n){
      if(nodes[n].parent==-1) {
         root=n;
         break;
      }
	}
	dfs(root);

   int mininv=numeric_limits<int>::max();
   vector<int> capitali;
	function<void(int,int)> dfs2 = [&](int invsofar, int i) {
	   int invtot=invsofar+nodes[i].invSotto;
      if (invtot<mininv) {
         mininv=invtot;
         capitali.clear();
      }
      if (invtot==mininv){
         capitali.push_back(i);
      }

      for(auto [to, dir] : nodes[i].children) {
         dfs2(invtot-nodes[to].invSotto-dir+!dir, to);
      }
	};

	dfs2(0, root);
   sort(capitali.begin(), capitali.end());
	out<<mininv<<"\n";
	for(int i=0;i<capitali.size();++i) {
      if (i!=0) out<<" ";
      out<<capitali[i]+1;
	}
}
