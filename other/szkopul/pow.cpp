#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007

struct Edge {
   int from, to, h;
   Edge(int f, int t, int _h) : from{f}, to{t}, h{_h} {};
};

struct Node {
   int parent=-1;
   int rank=0;

   int v=1;
   int h=0;
};

signed main() {
   int M, N, H;
   cin>>M>>N>>H;

   vector<Edge> edges;
   if (N>1) {
      for(int m=0;m<M;++m){
         for(int n=0;n<N-1;++n){
            int h;
            cin>>h;
            edges.push_back(Edge(m*N+n, m*N+n+1, h));
         }
      }
   }
   if (M>1) {
      for(int m=0;m<M-1;++m){
         for(int n=0;n<N;++n){
            int h;
            cin>>h;
            edges.push_back(Edge(m*N+n, (m+1)*N+n, h));
         }
      }
   }

   //for(auto e:edges)cerr<<e.from<<" "<<e.to<<" "<<e.h<<"\n"; cerr<<"\n";

   vector<Node> nodes(N*M);
   function<int(int)> getParent = [&](int i) -> int {
      //cerr<<i<<" "<<nodes[i].parent<<"\n";
      if (nodes[i].parent == -1) return i;
      return getParent(nodes[i].parent);
   };
   auto merge = [&](int i, int j, int h) {
      //cerr<<i<<" "<<j<<" "<<h<<"\n"<<flush;
      int pari = getParent(i);
      int parj = getParent(j);
      if (pari == parj) return;
      assert(nodes[pari].parent == -1);
      assert(nodes[parj].parent == -1);

      if (nodes[pari].rank > nodes[parj].rank) swap(pari, parj); // sicuramente pari.rank < parj.rank
      nodes[pari].parent = parj;
      nodes[parj].rank = max(nodes[parj].rank, nodes[pari].rank + 1);

      nodes[pari].v += h - nodes[pari].h;
      nodes[parj].v += h - nodes[parj].h;
      nodes[parj].h = h;
      nodes[parj].v = (nodes[parj].v * nodes[pari].v) % MOD;
   };

   sort(edges.begin(), edges.end(), [](Edge&a,Edge&b) {return a.h<b.h;});
   for (auto e:edges){
      merge(e.from, e.to, e.h);
   }

   int top=getParent(0);
   cout<<(nodes[top].v+(H-nodes[top].h))%MOD<<"\n";
}
