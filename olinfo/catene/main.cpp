#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll,ll>;

struct Node{
   int parent=-1;
   vector<ii> children;
};

long long profitto_massimo(int N, int U[], int V[], int W[]) {
   vector<Node> nodes(N);
   for(int n=0;n<N-1;++n){
      U[n]--; V[n]--;
      if(nodes[U[n]].parent==-1) swap(U[n],V[n]);
      nodes[U[n]].children.push_back({V[n], W[n]});
      nodes[V[n]].parent=U[n];
   }

   vector<ll> memPreso(N,-1);
   vector<ll> memNonPreso(N,-1);
   function<ll(int)> edgePreso;
   function<ll(int)> edgeNonPreso;

   edgePreso = [&](int i) {
      if (memPreso[i]==-1){
         ll diff=0;
         memPreso[i]=0;
         for(auto [to, w] : nodes[i].children){
            memPreso[i]+=edgeNonPreso(to);
            diff=max(diff, w+edgePreso(to)-edgeNonPreso(to));
         }
         memPreso[i]+=diff;
      }
      return memPreso[i];
   };

   edgeNonPreso = [&](int i) {
      if (memNonPreso[i]==-1){
         ll diff1=0, diff2=0;
         memNonPreso[i]=0;
         for(auto [to, w] : nodes[i].children){
            memNonPreso[i]+=edgeNonPreso(to);
            diff2=max(diff2, w+edgePreso(to)-edgeNonPreso(to));
            if(diff2>diff1)swap(diff2, diff1);
         }
         memNonPreso[i]+=diff1+diff2;
      }
      return memNonPreso[i];
   };

   for(int n=0;n<N;++n){
      if(nodes[n].parent==-1){
         return edgeNonPreso(n);
      }
   }
   return 0; //unreachable
}
